from setuptools import setup, Extension
import numpy

hist = Extension('imgproc.stats.hist._hist',
                 sources=["imgproc/stats/hist/src/module.c",
                          "imgproc/stats/hist/src/core/core.c"],
                 include_dirs=[numpy.get_include()],
                 libraries=["png"])

setup(name="imgproc",
      version="0.1",
      packages=["imgproc",
                "imgproc.stats",
                "imgproc.stats.hist"],
      ext_modules=[hist])
