import imgproc.stats.hist

if __name__ == "__main__":
    res = imgproc.stats.hist.hist("data/img4.png")
    res.plot("out/hist.pdf")
    print(res)
