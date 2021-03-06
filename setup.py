# setuptools supercedes distutils (mostly)
from setuptools import setup, Extension

pymongocrypt_module = Extension('pymongocrypt',
    sources = ['pymongocrypt.c', 'mongocrypt.c'])

# adding things to data_files just puts them in the egg.
setup (name = 'pymongocrypt',
        version = '0.1',
        description = 'A proof-of-concept',
        ext_modules = [pymongocrypt_module]
        )
