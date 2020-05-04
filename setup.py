from distutils.core import setup, Extension

module1 = Extension('dpyth', sources = ['dpyth.c'])

setup (name = 'dpyth',
       version = '1.0',
       description = 'Модуль для решения задач дискретной математики',
       ext_modules = [module1])
