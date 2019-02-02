An example of having PyMongo passing sockets down to libmongocrypt.

Try it:
```
$ git clone https://github.com/kevinAlbs/sockets-to-libmongocrypt
$ cd sockets-to-libmongocrypt
$ # create a virtual environment for python 3
$ python3 -m venv ./venv
$ . ./venv/bin/activate
$ python setup.py install
$ python pymongo-caller.py
ismaster response:
�...V.......�........�....ismaster...maxBsonObjectSize......maxMessageSizeBytes..l�..maxWriteBatchSize......localTime...j.h....logicalSessionTimeoutMinutes......connectionId.r....minWireVersion......maxWireVersion......readOnly...ok.......�..
```
