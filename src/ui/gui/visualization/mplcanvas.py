import matplotlib
matplotlib.use('Qt5Agg')

from matplotlib.backends.backend_qt5agg import FigureCanvasQTAgg
from matplotlib.figure import Figure


class MplCanvas(FigureCanvasQTAgg):
    def __init__(self, parent=None, width=5, height=4, dpi=100):
        fig = Figure(figsize=(width, height), dpi=dpi)
        fig.patch.set_facecolor('#1d1d1d')
        self.axes = fig.add_subplot(111)
        self.axes.set_facecolor('#1d1d1d')
        self.axes.spines['top'].set_color("#ffffff")
        self.axes.spines['bottom'].set_color("#ffffff")
        self.axes.spines['left'].set_color("#ffffff")
        self.axes.spines['right'].set_color("#ffffff")
        self.axes.tick_params(axis='x', colors='#ffffff')
        self.axes.tick_params(axis='y', colors='#ffffff')
        [t.set_color('#ffffff') for t in self.axes.xaxis.get_ticklabels()]
        [t.set_color('#ffffff') for t in self.axes.yaxis.get_ticklabels()]
        self.axes.xaxis.label.set_color('#ffffff')
        self.axes.yaxis.label.set_color('#ffffff')

        super(MplCanvas, self).__init__(fig)