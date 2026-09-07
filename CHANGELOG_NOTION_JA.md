# ERI Robotics QGroundControl 5.0

## カスタムAndroid版 リリース履歴

> このドキュメントは、QGroundControl 5.0.0をベースにしたERI Robotics向けAndroid版の履歴をまとめたものです。

`customN`のサフィックスは、APKのビルド世代を表します。アプリケーションの基本バージョンは、すべて**QGroundControl 5.0.0**です。各APKに埋め込まれたGitリビジョンによって、ビルドに使用されたコミット済みソースを特定しています。

同じリビジョンが埋め込まれているAPKは、コミット済みソースが同一です。ただし、ビルド設定、署名、パッケージング、ローカルのビルド状態などによって、APKの内容やチェックサムが完全に一致しない場合があります。

---

## バージョン概要

### v5.0.0-1.0.0

- **リリース種別：** 現在公開中の正式リリース
- **リリース日：** 2026-08-31
- **Gitタグのリビジョン：** `ed7500e09`
- **公開APKに埋め込まれたリビジョン：** `be0e48e27`
- **ソース上同等のカスタム版：** `v5.0.0-custom7`
- **重要：** 公開APKは、Gitタグが参照しているリビジョンからビルドされていません。
- **影響：** `custom7`より後に追加された機能は、現在の`v5.0.0-1.0.0` APKには含まれていません。
- **GitHubリリース：** https://github.com/ERI-Robotics-v2/qgroundcontrol/releases/tag/v5.0.0-1.0.0

### v5.0.0-custom11

- **リリース日：** 2026-06-02
- **埋め込みリビジョン：** `f50f27c87`
- **位置付け：** 保存されているカスタムAPKの中で最新のソース
- **GitHubリリース：** https://github.com/ERI-Robotics-v2/qgroundcontrol/releases/tag/v5.0.0-custom11

### v5.0.0-custom10

- **埋め込みリビジョン：** `c322549be`
- **位置付け：** `custom8`および`custom9`と同じコミット済みソース
- **GitHubリリース：** https://github.com/ERI-Robotics-v2/qgroundcontrol/releases/tag/v5.0.0-custom10

### v5.0.0-custom9

- **埋め込みリビジョン：** `c322549be`
- **位置付け：** `custom8`および`custom10`と同じコミット済みソース
- **GitHubリリース：** https://github.com/ERI-Robotics-v2/qgroundcontrol/releases/tag/v5.0.0-custom9

### v5.0.0-custom8

- **リリース日：** 2026-05-11
- **埋め込みリビジョン：** `c322549be`
- **位置付け：** `custom7`より新しいコミット済みソース
- **GitHubリリース：** https://github.com/ERI-Robotics-v2/qgroundcontrol/releases/tag/v5.0.0-custom8

### v5.0.0-custom7

- **リリース日：** 2026-04-01
- **埋め込みリビジョン：** `be0e48e27`
- **位置付け：** 公開中の`v5.0.0-1.0.0` APKと同じコミット済みソース
- **GitHubリリース：** https://github.com/ERI-Robotics-v2/qgroundcontrol/releases/tag/v5.0.0-custom7

### v5.0.0-custom6

- **埋め込みリビジョン：** `e12b1afe3`
- **位置付け：** `custom4`および`custom5`と同じコミット済みソース
- **GitHubリリース：** https://github.com/ERI-Robotics-v2/qgroundcontrol/releases/tag/v5.0.0-custom6

### v5.0.0-custom5

- **埋め込みリビジョン：** `e12b1afe3`
- **位置付け：** `custom4`および`custom6`と同じコミット済みソース
- **GitHubリリース：** https://github.com/ERI-Robotics-v2/qgroundcontrol/releases/tag/v5.0.0-custom5

### v5.0.0-custom4

- **リリース日：** 2026-03-19
- **埋め込みリビジョン：** `e12b1afe3`
- **位置付け：** `custom2`より新しいコミット済みソース
- **GitHubリリース：** https://github.com/ERI-Robotics-v2/qgroundcontrol/releases/tag/v5.0.0-custom4

### v5.0.0-custom3

- **状態：** データなし
- **APK：** 未提供
- **ソースリビジョン：** 不明
- **GitHubリリース：** 未作成

### v5.0.0-custom2

- **埋め込みリビジョン：** `ef4ff6dca`
- **位置付け：** `custom1`と同じコミット済みソース
- **GitHubリリース：** https://github.com/ERI-Robotics-v2/qgroundcontrol/releases/tag/v5.0.0-custom2

### v5.0.0-custom1

- **リリース日：** 2026-03-11
- **埋め込みリビジョン：** `ef4ff6dca`
- **位置付け：** このシリーズで最初に保存されたリビジョン
- **GitHubリリース：** https://github.com/ERI-Robotics-v2/qgroundcontrol/releases/tag/v5.0.0-custom1

---

## 機能別変更履歴

### v5.0.0-custom11

`custom10`で使用されたソースからの変更点です。

#### 設定とPiP

- 個別に配置されていたPiP操作を、共通の**設定**パネルへ統合しました。
- RTSP／PiP URL設定を追加しました。
- **PiPをクリア**する操作を追加しました。
- 現在使用中の通信先エンドポイント表示を追加しました。
- PiPウィンドウ内にあった個別のURL編集画面を削除しました。

#### VOXLセーフシャットダウン

- シャットダウン実行前の確認ダイアログを追加しました。
- カスタムMAVLinkメッセージ`CUSMVL_SAFE_SHUTDOWN`（`42010`）を追加しました。
- 要求の識別および重複判定に利用できるリクエストIDを追加しました。
- 送信中、成功、エラー、タイムアウトの状態表示を追加しました。
- 15秒の確認タイムアウトを追加しました。
- シャットダウン要求送信後のプライマリリンク切断を、シャットダウン完了として検出します。

#### 映像ストリームの復旧

- 再試行間隔を10～30秒の範囲で段階的に延長するバックオフ処理を追加しました。
- メイン映像とPiP映像の再起動処理を改善しました。
- ストリーム障害後に短時間で再起動を繰り返す動作を抑制しました。

#### フライトHUD

- ToFのON／OFF状態表示を追加しました。
- `CP_DIST`パラメーターに基づくBRK ON／OFF表示を追加しました。

#### ネットワーク

- 通信中のUDPピアのIPアドレスとポートを追跡できるようにしました。
- TCPおよび設定済みUDPエンドポイントを代替情報として使用する処理を追加しました。
- 現在の通信先を設定パネルに表示します。

---

### v5.0.0-custom8 ～ v5.0.0-custom10

3つのAPKにはすべて`c322549be`が埋め込まれています。`custom8`、`custom9`、`custom10`の間にコミット済みソースの変更はありません。

#### コントローラー

- G4コントローラー向けダイヤルキャリブレーション処理を追加しました。

#### フライトHUD

- HUDコンパスのレイアウトを調整しました。
- 相対位置表示をS／D／H形式へ変更しました。
- Wi-Fi強度をパーセント表示へ変更しました。

#### ステータスメッセージ

- `STATUSTEXT`エラー専用のオーバーレイ表示を追加しました。

#### UI

- レイアウトおよび表示を追加調整しました。

#### ビルド環境

- Windows向けカスタムビルドworkflowを追加しました。
- NSISインストーラー生成を追加しました。
- Linux向け診断workflowを追加しました。
- カスタムworkflowの上書き問題とQt StateMachine不足を修正しました。
- GitHub Actionsを手動実行専用へ変更しました。

---

### v5.0.0-custom7

#### コントローラー

- G4補助軸の正規化処理を追加しました。
- 補助軸のデバッグ情報を追加しました。

#### フライトHUD

- CPU温度表示を追加しました。
- デバッグ情報の表示を整理しました。

#### 録画UI

- 水準器と録画UIのレイアウトを調整しました。
- 追加の`REC_STAT`状態に対応しました。

---

### v5.0.0-custom4 ～ v5.0.0-custom6

3つのAPKにはすべて`e12b1afe3`が埋め込まれています。`custom4`、`custom5`、`custom6`の間にコミット済みソースの変更はありません。

#### 映像UI

- 水準器を画面左下へ移動しました。
- PiPウィンドウのサイズと位置を調整しました。
- 録画表示とカメラ操作UIのレイアウトを調整しました。
- メイン映像にクロスヘアを追加しました。

#### コントローラーとMAVLink

- RC補助軸の送信処理を追加しました。
- 録画状態の送信および表示を追加しました。
- 生値および±1000スケールでの実装を経て、`MANUAL_CONTROL`の正規化された補助軸値へ変更しました。

#### 録画ステータス

- 録画状態表示を追加しました。
- `REC_STAT`の表示文言と状態色を調整しました。

#### 通信

- 通信リンクを削除する際の動作を修正しました。

---

### v5.0.0-custom1 ～ v5.0.0-custom2

両方のAPKには`ef4ff6dca`が埋め込まれています。`custom1`と`custom2`の間にコミット済みソースの変更はありません。

#### Android UIとテレメトリー

- 初期のカスタムAndroid UIを追加しました。
- TIMESYNC送信を修正しました。

#### バッテリーテレメトリー

- 無効な拡張`BATTERY_STATUS`電圧値を無視するようにしました。

#### Android署名

- ローカルのAndroid署名設定を読み込めるようにしました。

---

## QGroundControl 5.0 ベースの変更点

- コンパスと姿勢表示を統合した計器を追加しました。
- デスクトップではクリック、モバイルでは長押しによる計器選択を追加しました。
- Fly ViewおよびJoystickの**Custom Actions**を**MAVLink Actions**へ名称変更しました。
- MAVLink Inspectorで個別のメッセージレートを設定できるようにしました。
- MAVLink 2署名を有効化しました。
- 設定可能なしきい値に応じて変化するバッテリーバーを追加しました。

---

## 正式リリース修正時の推奨手順

`v5.0.0-1.0.0`を`custom11`より後の正式版として扱う場合は、次の手順を推奨します。

1. 正式版として使用するソースリビジョンを決定します。
2. Gitタグがそのリビジョンを参照していることを確認します。
3. そのタグをクリーンチェックアウトした環境からAndroid APKを再ビルドします。
4. 公開前にAPKへ埋め込まれたリビジョンを確認します。
5. 検証済みAPKで現在のリリースアセットを置き換えます。

