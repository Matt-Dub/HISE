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

---

## NOTE 4 -- a soft bypassed synth freezes every meter attached to it -- *patched, unverified*

Found on the Dread Drumz mixer: a channel whose BP button is switched off leaves its VU meter lit
at the level of the last block it played, instead of falling to silence. It stays there for as long
as the channel is bypassed.

**Cause.** The peaks a `MatrixPeakMeter` reads live in `RoutableProcessor::MatrixData`, and the only
thing that writes them is `MatrixData::handleDisplayValues` (`hi_core/hi_dsp/Routing.cpp:459`),
called from the render callback -- `ModulatorSynthChain.cpp:415`, `ModulatorSynth.cpp:681`. A soft
bypassed chain returns before that:

```cpp
// ModulatorSynthChain::renderNextBlockWithModulators, ModulatorSynthChain.cpp:257
if (isSoftBypassed()) return;
```

So the array keeps its last value. The decay does not save it either: `UpDecayTime` /
`DownDecayTime` are applied inside `MatrixData::setGainValues` (`Routing.cpp:516`), which is reached
only through that same `handleDisplayValues`. No render, no decay. On the meter side
`MatrixPeakMeter::InternalComp::timerCallback` keeps ticking and keeps reading the same frozen
number, so nothing is wrong there.

**Fix.** `MatrixData::clearDisplayValues()` zeroes both `sourceGainValues` and `targetGainValues`,
and `ModulatorSynth::softBypassStateChanged` calls it when the synth goes into bypass. That callback
already runs on the sample loading thread with the voices killed, which is the same place the
bypass state itself is stored. Unbypassing needs nothing: the render callback starts writing again.

The meter drops to silence at once rather than decaying -- there is no audio left to decay from.
`ShowMaxPeak` clears on its own, its counter is driven by the meter's own timer.

Two things the first cut got wrong, both fixed on 2026-09-05:

- `clearDisplayValues` took a `ScopedTryReadLock` and returned silently when it failed, copying
  `setGainValues`. That is right for `setGainValues`, which runs every block and gets another
  chance on the next one; it is wrong here, because this is the *last* write the matrix ever gets
  before the processor stops rendering. A dropped try lock froze the meter for good. It now takes
  the blocking `ScopedReadLock` -- the same lock `setGainValues` writes under, the write lock only
  guarding a channel count change -- which is allowed because this is never the audio thread.
- Only the bypassed synth's own matrix was cleared. `ModulatorSynthChain` skips a bypassed child
  *before* `renderNextBlockWithModulators` (`ModulatorSynthChain.cpp:364`), so everything below the
  bypass stops rendering without ever getting a `softBypassStateChanged` of its own, and every
  `RoutableProcessor` down there freezes identically. `clearDisplayValuesRecursive` now walks the
  whole subtree. It walks `getChildProcessor` directly rather than using `Processor::Iterator`,
  whose constructor takes the iterator lock: this runs on the sample loading thread, which may hold
  the sample lock, and `LockHelpers` gives those two the same priority so they must not be nested.

  This one is engine-side only today. All 32 `MatrixPeakMeter` tiles in the Dread Drumz UI bind
  `containerChN`, `gainMaster` or a `send*Channel`, never a processor *inside* a container, so the
  channel bypass never hit the gap on this project. It would bite the moment a meter is pointed at
  an effect or a sampler under a container that can be bypassed.

**Not verified in a build yet.** The report that the bug was still live came from HISE built
2026-09-04 09:48 and `Dread Drumz.vst3` built 2026-09-05 08:57, both older than the 09:32 source
edit. Compare the binary mtime against the source before concluding anything about this one.

## NOTE 5 -- a two column preset browser never selects its bank column -- *patched, unverified*

Found on Dread Drumz (BUG 72): the kit browser comes up with the preset selected on the right and
**nothing** selected in the bank column on the left, so the user can read which preset is loaded but
not which bank it belongs to. `NumColumns: 2` in the floating tile data.

**Cause, two paths.**

*Construction.* `numColumns` is `3` by default (`PresetBrowser.h:292`). The constructor calls
`showLoadedPreset()` (`PresetBrowser.cpp:586`) **before** `setOptions()` applies the layout the
interface actually asks for. Under three columns that function computes

```cpp
File category = f.getParentDirectory();
File bank = category.getParentDirectory();
if (numColumns == 2) bank = category;      // not taken: numColumns is still 3
bankColumn->setSelectedFile(bank, dontSendNotification);
```

so it looks for the preset's *grandparent* directory in a column that lists its *parents*.
`ColumnListModel::getIndexForFile` returns -1 and `setSelectedFile` falls through to
`listbox->deselectAllRows()`. `setNumColumns()` then only called `resized()`, so nothing ever
selected it again.

*Every later load.* `presetChanged()` (`PresetBrowser.cpp:822`) short-circuits to the preset column
alone when `allPresets[currentlyLoadedPreset] == newPreset`. That is not the exception, it is the
common path: a preset loaded from outside the browser -- a host restoring its state, the prev/next
buttons, a script call -- reaches the callback with `currentlyLoadedPreset` already pointing at it.
The bank column was never touched.

**Fix.** Three pieces:

- `setNumColumns()` re-runs `showLoadedPreset()` when the count changes, so the columns are settled
  against the layout now in force. Guarded to skip single column mode, where `rebuildAllPresets()`
  has just re-rooted the preset column at the library root to list every preset flat and
  `showLoadedPreset()` would narrow it back to one folder.
- the short-circuit in `presetChanged()` calls the new `selectParentColumnsFor(newPreset)`.
- `selectParentColumnsFor()` selects the bank (and, with three columns, the category) column
  *without* re-rooting. `showLoadedPreset()` re-roots as it goes, which would scroll the user away
  from whatever they were browsing -- fine when the browser is being set up, wrong on every preset
  change.

Both paths were read off the source rather than observed under a debugger: the plugin-side symptom
matches (blank bank column at startup, and after `Engine.loadUserPreset`), and rebuilding the tile
through `setContentData` -- constructor, hence `showLoadedPreset()` under the wrong column count --
did not restore it either, which is what pointed at the constructor ordering.

**Verified 2026-09-11.** In the HISE IDE: the bank column selects correctly both when a preset is
loaded by script and when the load lands in a different bank, with the preset column re-rooting as
before. The Dread Drumz author then confirmed the exported plugin compiles and works in REAPER.
