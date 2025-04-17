# RaspiPicoTracer_Prototype_V3
RaspiPicoTracerは白線の上をたどって走るロボットであり、
機能をできる限り少なくし、回路、メカ、組み立て、プログラミングなどロボット作成に必要な経験を一通り短期間で行えるように開発中です。
このロボットはマイクロマウス大会のロボトレース競技に参加することを想定して作成しています。
競技の詳細はロボトレース競技規定をご確認ください。

https://www.ntf.or.jp/?page_id=68

# 開発環境について
VSCodeでRaspberry Pi PicoのExtensionを使用します。
Raspberry Pi財団が公開しているドキュメント「Getting started with Raspberry Pi Pico-series」の内容に沿って行ってください。

cloneした後はImport Projectを行ってください。

# 回路図
![CircuitDiagram](https://github.com/Yumizu0406/RaspiPicoTracer_Prototype_V3/blob/main/document/circuit/RaspiPicoTracer_Prototype_V3.png)

# 部品表

| 名称 | メーカー | 値段 | 個数 | 備考 |
| ---- | ---- | ---- | ---- | ---- |
| Raspberry Pi Pico 2 | ラズベリーパイ財団 | 1000 | 1 | Raspberry Pi Picoでも可 |
| ダブルギヤボックス（左右独立４速タイプ） | 株式会社タミヤ | 924 | 1 | ギヤ比12.7:1で利用 |
| トラックタイヤセット （36mm径） | 株式会社タミヤ | 396 | 1 | - |
| 電池ボックス 単3×4本 リード線・フタ・スイッチ付 | COMFORTABLE ELECTRONIC CO., LTD(COMF) | 160 | 1 | - |
| 耐熱電子ワイヤー 黒色 20m 導体外径0.54mm(AWG24相当) | 住友電気工業株式会社 | 600 | 1 | モータードライバとモーター接続用<br>15cmのものを4つ利用 |
| TB6612モータードライバー ブレークアウトボードキット | 秋月電子 | 380 | 1 | 1 |