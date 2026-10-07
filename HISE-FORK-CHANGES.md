# HISE-FORK-CHANGES

Liste des modifications du fork `Matt-Dub/HISE` (branche `custom-develop`) par rapport a
`christophhart/HISE` (`upstream/develop`). Notes de travail : `SOUNDFINGERS-NOTES.md`.
Bugs moteur analyses en detail : `BUGS-NOTES.md`.

Etat au 2026-10-07 (HEAD `18f5d62eb`). Dernier merge upstream : `07b0614ee` (2026-09-04).

Regenerer la liste brute :

```
git fetch upstream
git log --no-merges --format="%h %ad %an | %s" --date=short upstream/develop..custom-develop
git diff $(git merge-base custom-develop upstream/develop) custom-develop --stat
```

Rappel : un fix moteur n'atteint le plugin qu'apres rebuild de HISE **et** re-export du plugin.
Les modifs JUCE ne sont compilees que dans l'export (pas dans HISE.app) : un re-export suffit.

---

## 1. Depots et sous-modules

| Element | Fork | Upstream |
|---------|------|----------|
| HISE | `origin` = `Matt-Dub/HISE`, branche `custom-develop` | `upstream` = `christophhart/HISE` (jamais de push) |
| JUCE (sous-module) | `origin` = `Matt-Dub/JUCE_customized`, branche `custom-develop` | `upstream` = `christophhart/JUCE_customized`, branche `juce6` |

- `8fbd4368e` `.gitmodules` suit `custom-develop` de `JUCE_customized`.
- Workflow detaille (merge upstream, bump du pointeur JUCE) : `SOUNDFINGERS-NOTES.md`, section Workflow Git.

### Commits propres au JUCE du fork

| Commit JUCE | Date | Changement |
|-------------|------|------------|
| `3010fb4` | 2026-09-18 | `Bus::setName` + `ChangeDetails::ioChanged` -> `Vst::kIoTitlesChanged` (renommage des sorties VST3 a chaud). Utilise par `Engine.setOutputBusName`. |
| `9dd2caf` | 2026-10-03 | AU : `AudioProcessorChangedUpdater` toujours differe (`triggerAsyncUpdate`). Une seule notification `ParameterList` au lieu d'une par controle. Ouverture UI Dread Drumz dans Logic ~35 s -> ~15 s. |

---

## 2. Correctifs moteur (Mathieu)

| Commit | Date | Changement |
|--------|------|------------|
| `18f5d62eb` | 2026-10-07 | ComboBox a sous-menus (`useCustomPopup`) : la categorie d'une valeur posee par script (`setValue`, `set("items")`) n'etait pas cochee, l'en-tete gardait la coche du dernier choix a la souris. `refreshTickState()` dans `ComboBoxWrapper::updateValue` et `updateItems`. |
| `280bfa008` | 2026-10-06 | Alertes scriptees (`drawAlertWindow`) : plus d'ombre native Windows autour de la marge transparente de 50 px (`ScriptedLookAndFeel::Laf::getAlertBoxWindowFlags`). |
| `ae96c8396` | 2026-10-01 | `ScopedNoDenormals` sans effet sur arm64 -> pose FPCR.FZ. IR de convolution reechantillonnee sans compensation de gain (+6.8 dB pour une IR 44.1 kHz a 96 kHz). `setDamping` reconstruisait l'IR a chaque ecriture. |
| `1ea0f1335` | 2026-09-27 | Convolution : crash au changement d'IR avec un chemin mono. |
| `bc062d864` | 2026-09-15 | `MasterEffectProcessor` : remise a zero de `numSilentBuffers` au reveil d'un effet suspendu (un delay se re-suspendait et avalait l'echo). |
| `72dee8fcf` | 2026-09-11 | mcl : `getUnderlines` borne sur le cache de glyphes, pas sur le document (segfault en dessinant un soulignement d'erreur, NOTE 1 de `BUGS-NOTES.md`). |
| `5ef89b6bc` | 2026-09-10 | PresetBrowser 2 colonnes : la colonne banque du preset charge est selectionnee. |
| `af7e75e04` | 2026-09-06 | PresetBrowser : favoris OK dans les dossiers dont le nom contient des parentheses. |
| `e2ccf44ee` | 2026-09-05 | VU figes au soft-bypass : `clearDisplayValues()` depuis `ModulatorSynth::softBypassStateChanged`. |
| `49cd3d2db` | 2026-09-04 | `validateEventObject` : le message d'erreur donne le bon niveau de callback (Drag). |
| `cfd2705fe` | 2026-09-03 | `MatrixData::numAllowedConnections` initialise (-1). Avant : matrices > 2 connexions elaguees au hasard. |
| `19ae6ede5` | 2026-08-23 | `MatrixPeakMeter` fige au silence depuis le merge upstream `5ad80f27c` (coefficient de `setGainValues` inverse). |
| `39c00bcf2` | 2026-08-10 | Standalone : ID machine de licence calcule comme dans les exports. |
| `2a4984719` | 2026-08-06 | `PooledUIUpdater` n'appelle plus de virtuelles pures sur un objet en destruction (abort de Logic). |
| `cc59f741e` | 2026-08-06 | `SimpleTimer::startOrStop` : test null de l'updater. |
| `9d8ab92b1` | 2026-07-16 | Race cross-thread sur `ValueTree` dans le dispatch asynchrone des proprietes (UAF lors de changements de preset rapides). Snapshot de la valeur au moment de la notification. PR #2 (`fix-race-bug`). |
| `48e07b56e` | 2026-07-11 | `getZoomLevel()` renvoyait NaN si `SCALE_FACTOR` corrompu. PR #1. |
| `0c26928b5` | 2025-10-20 | Icone de drag MIDI qui disparaissait : `MidiOverlayFactory` n'est plus `DeletedAtShutdown` (fuite potentielle a surveiller). |

## 3. Performances (Mathieu)

| Commit | Date | Changement |
|--------|------|------------|
| `064472a63` | 2026-10-05 | `analyse.fft` : un moteur FFT par ordre partage par tout le process (`SharedResourcePointer`), verrou par moteur. -74 Mo a 1 instance. |
| `1db4c384d` | 2026-08-23 | `analyse.fft` : moteur FFT mis en cache (etait recree ~30 fois/s par noeud). |
| `7251c273a` | 2026-10-04 | Metadonnees de script : parametres ajoutes en place (boucle quadratique). Instanciation AU 5.34 s -> 4.57 s. |
| `28cb88416` | 2026-09-15 | `HISE_SKIP_IDLE_SYNTH_BLOCKS` (defaut 0) : samplers et conteneurs inactifs sautent le bloc entier. |
| `a78423054` | 2026-09-03 | `GainEffect` (SimpleGain) se suspend sur silence. |
| `ad49d3060` | 2026-09-06 | Convolution : NEON natif / FMA3 pour la multiplication complexe, predelay par bloc. |
| `416880ef5` | 2026-09-06 | Convolution : fusion de l'etage head et du premier etage tail, pas de rechargement d'IR redondant. |
| `7f7725b59` | 2026-08-23 | `MatrixPeakMeter` : repaint seulement si la valeur change d'au moins un pixel. |

## 4. API script et LAF

### Ajouts de Mathieu

| Commit | Date | Changement |
|--------|------|------------|
| `841f238c5` | 2026-09-18 | `Engine.setOutputBusName(busIndex, name)` (necessite JUCE `3010fb4`). |
| `7a6a0e15b` | 2026-09-25 | `Engine.canUndo()` / `Engine.canRedo()`. |

### Lot LAF / UI (sessions Claude, fevrier-mars 2026)

- Alertes : fond transparent et marge de 50 px quand `drawAlertWindow` est defini, `obj.area` (contenu) + `obj.bounds` (fenetre entiere) (`a0b3c0153`).
- Value popup : plus de fond carre derriere un popup arrondi (`668de7b41`), couleurs issues de variables externes dans `Content.setValuePopupData` (`31b841618`).
- `drawPerformanceLabel` : nouvelle fonction LAF (RAM en octets bruts, alias de police) (`54a64b7c8`, `b52537bc8`, `fb48c2119`).
- Polices : `fontName` complet (avec style Bold/Medium) passe aux callbacks LAF via `FloatingTileContent::getFontName()` (`13835296e`, `500e3bbd7`, `42711ac2d`, `c12f211e6`), `font`/`fontSize` dans `drawWhiteNote`/`drawBlackNote` (`e1c7f1048`) et dans les LAF du PresetBrowser (`1eecaf393`).
- MidiLearnPanel / FrontendMacroPanel : LAF scripte (`35d36232e`, `b2fdf9be0`), propriete `ColumnWidthRatio` (`98eb880b2`, `3a8bdee1c`), colonnes de table routees vers le LAF (`f40c25bd3`, `2b2900d02`, `5a8e74c81`), `InvertedButton` devient un ToggleButton (`73a941a62`).
- `drawScrollbar` : recoit les proprietes et couleurs du floating tile, la largeur de colonne ne retire la scrollbar que si elle est visible (`2a2bb70d6`, `f898678e3`, `da5d32dcb`, `13d791b7c`).
- `drawLinearSlider` / `drawToggleButton` : proprietes du floating tile, `itemColour3`, textbox masquee si le LAF est actif (`f14671bf6`, `32c7ad8ce`, `5182faf83`, `7bdc600dc`).
- PresetBrowser : boutons de gestion des expansions (`6bcc0f39f`), recherche dans toutes les expansions + propriete `FullPathSearch` (`7ddc2bb4a`), filtre favoris multi-expansions (`21e432e90`).
- CustomSettings : propriete `LabelAlignment` (`7bd2da92e`).
- Divers : `String.fromCharCode` accepte une chaine hexa (`1948c9f3f`), `g.drawFittedText` enregistre (`730652121`), includes relatifs dans les scripts (`8915f00f3`, `6eb2f216e`), `Engine.loadFontAs` en chemin relatif (`226e9e6ed`).

## 5. Fork de David Healey (merge du 2026-03-12, `f6f9a31f3`)

~340 commits de `davidhealey/HISE` (2021-2026) integres au fork. Principaux themes :

- API script : `Engine.showMessageBoxWithCallback`, `Engine.setPreloadMessage`, `Engine.getSystemStats` (+ `isDarkModeActive`), `Engine.quit`, `Engine.getTempoName`, `Engine.intToHexString`, `Content.componentExists`, `Content.getInterfaceSize`, `Content.isCtrlDown`, `Colours.toHsl/fromHsl`, `Array.shift/concat`, `Object.keys`, `String.parseAsJSON`, `String.capitalize`, nombreuses fonctions `File`/`FileSystem` (rename, move, copy, copyDirectory, getHash, getSize, hasWriteAccess, isOnHardDisk, getZippedItemList...), methodes de `Rectangle`, tables scriptees (reset/set/addPoints), matrices (`getNumSourceChannels`...).
- LAF : `drawAhdsrBackground`, `drawTableBackground`, `enabled` sur boutons/sliders/tables/ahdsr, fond de popup menu transparent + `area`, pas d'ombre sur les popup menus LAF sous Windows, couleurs du filtergraph, `columnIndex`...
- PresetBrowser / expansions : nombreuses proprietes de mise en page, favoris d'expansion sans chargement, `FullPathFavourites`, barre de recherche masquable, corrections des expansions completes (Full Instrument Expansion).
- EQ draggable : `HandleSize`, evenements broadcaster `BandMoved`/`QChanged`/`MouseOver`.
- Build : Linux (Faust, IPP, FFTW, polices, Projucer), templates de projet (CURL, FFTW, plist macOS), VS2026.
- Taille de police globale de l'UI HISE passee a 16 px (`hi_tools/Macros.h`).

## 6. Defines et configuration

| Define / fichier | Fork | Upstream | Commit |
|------------------|------|----------|--------|
| `NUM_MAX_CHANNELS` (`hi_tools/Macros.h`) | 48 | 16 | `cdeb6a408` |
| `HISE_SILENCE_THRESHOLD_DB` (`hi_tools/Macros.h`) | 80 | 60 | `cdeb6a408` |
| `TempoSyncer::Tempo` (`hi_tools/hi_tools/MiscToolClasses.h`) | trie par duree decroissante | groupe (1/2D, 1/2, 1/2T...) | `d074fea84`, `358fcdf3c` |
| `HISE_SKIP_IDLE_SYNTH_BLOCKS` | nouveau, defaut 0 | absent | `28cb88416` |
| `.jucer` standalone / plugin | preprocesseurs projet, sorties multiples, AAX SDK 2.8, Faust Windows/macOS, sans `/arch:AVX`, `CompileWithDebugSymbols` corrige | - | `0e6baafcc`, `9aa58c215`, `d0e7314d2`, `b9ef1c636`, `c85f64c5a`, `4350907ba` |

**Attention a l'enum des tempos** : une dll scriptnode ou un plugin compile contre un autre ordre
(upstream ou ancien fork) joue la mauvaise valeur pour toutes les entrees D/T, alors que les valeurs
simples restent justes. Tout recompiler sur la meme source.

## 7. Modifs abandonnees ou disparues

- `f5020749e` molette de souris transmise au callback souris des scripts : revertee (`6e0e28356`). Restaurable en revertant le revert.
- `972b1b753` sortie anticipee de `SlotSender::flush` : revertee (`1179259ef`).
- `53ef33fcd` / `0e2e3ee1e` suspend-on-silence de CurveEq desactive : plus de difference avec upstream (ecrase par un merge).
- `c7197c950` contournement du crash "External Display buffer" (`ConstReference::isConstant`) : plus de difference avec upstream.
- Fork Healey : includes relatifs et `HISE_USE_EXPANSION_COMPANY_SUBFOLDERS` revertes cote Healey.

## 8. Problemes connus non corriges

- `HiseAudioThumbnail::LoadingThread` : use-after-free lors de changements de preset rapides (Ableton/Windows).
- `~AsyncValueTreePropertyListener` n'appelle jamais `state.removeListener(this)` (listener pendant possible).
- Wrapper AU : `kAudioUnitProperty_ParameterStringFromValue` dereference `pv->inValue` sans test NULL.
- `MidiDropper` sous Linux/Bitwig : pas de `XdndAware`, le drop est ignore.
