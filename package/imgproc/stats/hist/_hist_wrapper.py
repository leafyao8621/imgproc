import typing
import numpy
import matplotlib.pyplot
import imgproc.stats.hist._hist

class Hist:
    def __init__(self,
                 hist: numpy.ndarray,
                 histr: numpy.ndarray,
                 histg: numpy.ndarray,
                 histb: numpy.ndarray):
        self.hist = hist
        self.histr = histr
        self.histg = histg
        self.histb = histb
    def __str__(self):
        return f"Hist:\n{self.hist}\n" +\
               f"Histr:\n{self.histr}\n" +\
               f"Histg:\n{self.histg}\n" +\
               f"Histb:\n{self.histb}\n"
    def __repr__(self):
        return f"Hist:\n{self.hist}\n" +\
               f"Histr:\n{self.histr}\n" +\
               f"Histg:\n{self.histg}\n" +\
               f"Histb:\n{self.histb}\n"
    def plot(self, fn: typing.Union[None, str]):
        matplotlib.pyplot.clf()
        matplotlib.pyplot.bar(numpy.arange(256), self.hist)
        matplotlib.pyplot.savefig(fn)


def hist(fn: str) -> Hist:
    """[summary]

    Args:
        fn (str): [description]

    Returns:
        Hist: [description]
    """
    hist = numpy.empty(256, dtype=numpy.uintc)
    histr = numpy.empty(256, dtype=numpy.uintc)
    histg = numpy.empty(256, dtype=numpy.uintc)
    histb = numpy.empty(256, dtype=numpy.uintc)
    imgproc.stats.hist._hist.hist_base(fn, hist, histr, histg, histb)
    return Hist(hist, histr, histg, histb)
