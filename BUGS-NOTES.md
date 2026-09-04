# BUGS-NOTES

Fork-side defects found while working on **Dread Drumz**, kept here because they live in HISE
rather than in the plugin project. The plugin-side tracker is `~/GitHub/Dread-Drumz/BUGS-TO-FIX.md`;
entries there that turn out to be engine bugs get cross-referenced from this file.

Status vocabulary: **open** (reproducible), **latent** (the faulty code is still there but the
trigger is gone), **fixed** (patched here, with the commit).

---

## NOTE 1 -- `mcl::TextEditor::Error::rebuild()` segfaults on an error underline -- *latent*

Cross-reference: BUG 68 in the Dread Drumz tracker.

**Symptom.** HISE dies with `EXC_BAD_ACCESS` / `KERN_INVALID_ADDRESS at 0x10` on the JUCE Message
Thread while *drawing* a compile-error underline -- not while compiling. Because the process dies
before the REST reply is flushed, a `POST /api/recompile` just returns an empty body.

```
mcl::TextDocument::getUnderlines(mcl::Selection const&, mcl::TextDocument::Metric) const
mcl::TextDocument::getUnderlines(...)                       <- inlined
mcl::TextEditor::Error::rebuild()
mcl::TextEditor::updateAfterTextChange(juce::Range<int>)::$_0
juce::MessageQueue::runLoopSourceCallback
```

**Two unguarded dereferences on that path**, one of them the culprit:

- `hi_tools/mcl_editor/code_editor/TextDocument.cpp:1223` --
  `lines.lines[l]->getUnderlines({ left, right }, !s.isSingular())`. The index `l` is validated
  with `isPositiveAndBelow(l, getNumRows())`, but the subscript happens on `lines.lines`, a
  *different* array. When the document has been replaced and `lines.lines` has not been
  re-synchronised yet, the index passes the guard and reads out of bounds. The crash report points
  here.
- `hi_tools/mcl_editor/code_editor/TextEditor.cpp:1099` and `:1104` --
  `errorLines[0].getLength()` and `document.getSelectionRegion(errorWord).getRectangle(0)`, neither
  checked for an empty array. `getUnderlines` returns empty when every targeted row is folded or
  out of range, i.e. exactly the case above.

Working hypothesis: an `Error` left over from a previous compile keeps line/column positions into
a document the recompile has since replaced, and `updateAfterTextChange` rebuilds it against the
new one.

**Not the realtime-safety analyser.** The obvious suspect was
`hi_scripting/scripting/engine/JavascriptEngineParser.cpp:3341`, which raises
`"Unsafe API call in audio-thread callback: ..."`. It is gated on `strictness > SL::Unsafe` and only
*throws* at `SL::Strict` (`:3327`). `JavascriptProcessor::getStrictnessLevel()`
(`hi_scripting/scripting/ScriptProcessor.cpp:919`) reads
`HiseSettings::Scripting::CallScopeWarnings`, and on the macOS dev machine
`~/Library/Application Support/HISE/ScriptSettings.xml` carries
`<CallScopeWarnings value="Unset"/>` -> `SL::Unset`, which is `0` in
`enum class StrictnessLevel { Unset, Unsafe, Warn, Strict }`
(`hi_scripting/scripting/api/ScriptingBaseObjects.h:277`). `0 > 1` is false, so the block never
runs there. On a machine set to `Strict` it does, and that is the configuration in which
`hise-cli script compile` rejects scripts calling `getSliderValueAt` from `onNoteOn`.

**History.** Reproduced 4 times on 2026-09-04 against the build of `cfd2705fe`, at roughly one
module in ten during a sweep of recompiles, landing on a *different* module each time
(`midiHumanizer`, `midiPlayCh4`, `midiPlayCh18`, once between `midiPlayCh11` and `midiPlayCh12`) --
each of which recompiled cleanly in another session. So it was never tied to a particular script.

**Now latent, on `07b0614ee`.** `git diff cfd2705fe..HEAD -- hi_tools/mcl_editor/` is empty: both
dereferences above are byte-identical. What went away is the trigger, most plausibly `49cd3d2db`
(*report the actual required callback level in `validateEventObject`*), which removes a spurious
compile error -- no error, no marker, no rebuild, no crash.

Verified on the 09:48 build of `07b0614ee`: 3 full sweeps of the 25 Dread Drumz script processors,
**75 recompiles, 0 crashes**, no diagnostic reports written. Then the crash path was exercised
head-on -- a real syntax error injected into `scriptFlamCatcher.onNoteOn` through
`POST /api/set_script`. The compiler now *returns* the error
(`Found ';' when expecting an expression` at `scriptFlamCatcher.js:3:37`) instead of taking the
process down; 3 further recompiles with the error marker live, then 5 other modules recompiled on
top, all survived.

**To do**
- [ ] Bound the subscript on `lines.lines` in `getUnderlines`, rather than trusting `getNumRows()`.
- [ ] Guard `errorLines` / `getSelectionRegion` against an empty array in `Error::rebuild`.
- [ ] Decide whether a stale error marker should simply be invalidated when the document is
      reloaded, instead of rebuilt.

---

## NOTE 2 -- `AutoStartRestServer` never matches its stored value -- *open*

`hi_backend/backend/BackendRootWindow.cpp:1003` starts the REST server when the setting compares
equal to the string `"Yes"`:

```cpp
else if (bp->getSettingsObject().getSetting(HiseSettings::Scripting::AutoStartRestServer).toString() == "Yes")
```

but `~/Library/Application Support/HISE/ScriptSettings.xml` stores it as
`<AutoStartRestServer value="1"/>`. Observed on macOS: with that setting present, launching through
`open -a` binds nothing on port 1900, and every MCP runtime tool reports "cannot connect" against a
HISE that looks perfectly healthy on screen.

Workaround -- launch the inner binary with the command-line flag, which takes the other branch
(`BackendProcessor::isUsingCommandLineServerMode()`):

```bash
nohup ".../HISE.app/Contents/MacOS/HISE" start_server -port:1900 >/tmp/hise.log 2>&1 &
```

**To do**
- [ ] Normalise the boolean the way the other `"Yes"`/`"No"` flags are handled, or compare against
      both spellings.

---

## NOTE 3 -- `GET /api/status` reports a stale `commitHash` -- *open*

On the 2026-09-03 19:20 build, whose tree was at `cfd2705fe`, `/api/status` reported
`"commitHash": "e93c0c8dc96e52eba51ea5ef93bdbc483c922073"` -- dated 2026-08-10, ten commits behind.
The hash comes from a generated header that is not regenerated on every build, so it cannot be used
to tell which commit a running HISE was built from. Compare the binary's mtime against
`git log --date=iso` instead.

**To do**
- [ ] Regenerate the hash as a build step, or drop the field rather than report it wrong.
