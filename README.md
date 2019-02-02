An example of having PyMongo passing sockets down to libmongocrypt.

Try it (with a mongod running):
```
$ git clone git@github.com:kevinAlbs/sockets-to-libmongocrypt.git
$ cd sockets-to-libmongocrypt
$ python3 -m venv ./venv
$ . ./venv/bin/activate
$ pip install pymongo
$ python setup.py install
$ python pymongo-caller.py
ismaster response:
�...V.......�........�....ismaster...maxBsonObjectSize......maxMessageSizeBytes..l�..maxWriteBatchSize......localTime...j.h....logicalSessionTimeoutMinutes......connectionId.r....minWireVersion......maxWireVersion......readOnly...ok.......�..
```
