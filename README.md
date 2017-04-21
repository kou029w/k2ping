# k2ping

[![Build Status](https://travis-ci.org/kou029w/k2ping.svg?branch=develop)](https://travis-ci.org/kou029w/k2ping)

安価に製作できるpingでの死活監視装置です。

[![Thumbnail](https://i.ytimg.com/vi/O8T0brdBYlI/maxresdefault.jpg)](https://www.youtube.com/watch?v=O8T0brdBYlI)

## Getting Started

### Prerequisites

以下の材料を用意し、組み立てる必要があります。

- [WeMos D1 (ESP8266)](https://www.wemos.cc/product/d1.html)
- [LCD Keypad Shield For Arduino](https://www.dfrobot.com/product-51.html)
- USB to Micro-B Cable
- [PlatformIO Core](http://docs.platformio.org/en/latest/installation.html) がインストールされた PC or Mac

```
git clone git@github.com:kou029w/k2ping
cd k2ping
```

あらかじめ自分のWi-Fi環境に合わせて `src/k2ping.ino` の `network-name` と `pass-to-network` を変更する必要があります。

```arduino
  WiFi.begin("network-name", "pass-to-network");
```

### Installing

```
pio lib install 1526 # Install the LiquidCrystal library.
pio run --target upload
```

## Authors

* **Kohei Watanabe** [kou029w](https://github.com/kou029w)

See also the list of [contributors](https://github.com/kou029w/k2ping/contributors) who participated in this project.

## License

This project is licensed under the LGPL License - see the [LICENSE](LICENSE) file for details.

## Acknowledgments

* [dancol90/ESP8266Ping](https://github.com/dancol90/ESP8266Ping) を参考にさせて頂きました。作者に感謝します。
