# Chuni-SFX-Disabler

Chunithm 背景动画与音符特效禁用工具。

## 前言

当你兴冲冲地运行中二节奏，并准备开一把你最爱的歌曲时，你是否注意到，每个ExTap都牵动着你的心跳？不是它令人沉醉的打击感，而是它带来的令你尤其是你的电脑震撼的粒子特效。</br>
如果你遇到过黄键海特效爆炒你的GPU导致严重掉帧，如果你曾为精美的背景动画实时渲染爆炒你的GPU而打不了歌，那么这篇教程或许可以帮到你大忙。你只需要移除一点点东西，你的游戏体验将会得到大幅度的提高。

## 注意

本教程**不为**操作不当而错删文件而负责。

因此，强烈建议你将本教程出现的**删除**视为在当前文件夹新建一个文件夹（如 `DISABLED`等），将你要删除的文件移动进去，而非真的删除。这样的好处是，你可以随时恢复你要删除的文件。而且那些文件相比剩下的部分只是九牛一毛，删除了也节省不了多少储存空间。

## 方法1：使用本工具

在[Release](https://github.com/AstroNot233/Chuni-SFX-Disabler/releases/latest)中，获取压缩包并解压，简单工具即开即用。

运行后选择游戏根目录，工具将通过`segatools.ini`找到你的option目录以解决兼容性问题，如果识别错误，也可以手动指定。

在**背景动画**栏下，有2个按钮，左侧为禁用所有谱面背景，右侧为重新启用所有谱面背景。

在**音符特效**栏下，可以通过勾选复选框选择希望**禁用**的特效；再点击上方的2个按钮，左侧为禁用所选音符特效，右侧为重新启用所有音符特效。

## 方法2：手动删除文件

为方便表述，记游戏根目录为`%root%`，option目录为`%option%`，data目录为`%data%`。

在`%root%`中，您应当可见`bin`, `data`, `firm`, `license`目录。

### 删除背景动画

背景动画分布散乱，储存在`%data%\A000\stage\`和`%option%\A...\stage\`中，其中`.`表示任意单个字符。

您需要手动将`%data%\A000\stage`和所有`%option%\A...\stage`**删除**。

### 删除音符特效

音符特效全部储存在`%data%`中。

#### 关于删除

首先请进入`%data%\uvc`，所有文件皆可**删除**。

然后进入`%data%\acroarts`，请务必**保留**以下文件（按字母升序）：

* `chu_count_border.afb`
* `chu_count_border_s.afb`
* `chu_count_chain.afb`
* `chu_count_combo.afb`
* `chu_count_combo_s.afb`
* `chu_count_score.afb`
* `chu_count_score_s.afb`
* `CHU_EF_Tap_KeyBeam_v10.afb`
* `CHU_EF_Tap_text_v10.afb`
* `CHU_EF_Tap_textAirAction_v10.afb`
* `ColorFilter120FPS.afb`
* `nf_gamecamera.afb`
* `st_effect_use_list.afb`

#### 关于保留

如果您很喜欢某种音符的特效，而您的显卡并非极其吃力，您或许会希望保留一部分音符特效。您可以根据以下对照表保留一部分文件。

在`%data%\acroarts`中：

|音符|特效对应文件（大小写无关）|备注|
|:-:|:-:|:-:|
|EXTAP|以`chu_ef_ex`开头||
|AIR|以`chu_ef_air`开头|但不以`chu_ef_airhold`开头|
|AIRHOLD|以`chu_ef_airhold`开头||
|TAP|以`CHU_EF_Tap`开头|但实际上可供删除的文件只有`~_bomb_v10.afb`和`~_reaction_v10.afb`|
|SLIDE|以`CHU_EF_Slide`开头||
|FLICK|以`CHU_EF_Flick`开头||
|DAMAGE|以`chu_ef_dmg`开头||

在`%data%\uvc`中：

|音符|特效对应文件（大小写无关）|
|:-:|:-:|
|EXTAP|`ntt_extap_nml.uvc`|
|AIR|`ntt_airlad.uvc`和`ntt_airup.uvc`|
|AIRHOLD|`ntt_ahact.uvc`和`ntt_ahsdw.uvc`|
|DAMAGE|`ntt_dmg.uvc`|

## 注

禁用音符特效有极小概率导致游戏在启动时由于缺少文件崩溃。此崩溃无法稳定复现、出现原因不明，但重新启动游戏通常会解决此问题，且启动成功后在游戏中不会因此而崩溃。若重新启动游戏仍然崩溃，可以尝试重启计算机。若仍然无法解决，可以还原音符特效正常启动游戏一次，再将音符特效重新禁用。</br>
禁用背景动画不会导致启动时与运行时崩溃。
