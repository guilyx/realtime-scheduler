import matplotlib.pyplot as plt
import numpy as np
import argparse

class GanttPlot():
    def __init__(self, ylim, xlim, title=None):
        self.fig, self.gnt = plt.subplots(figsize=(12, 8))
        self.gnt.set_ylim(0, ylim+1)
        self.gnt.set_xlim(-1, xlim+1)
        self.ylim = ylim
        self.xlim = xlim
        self.tasksYticks = {}
        self.tasksColors = {}
        self.tasks = {}

        # Setting labels for x-axis and y-axis
        self.gnt.set_xlabel('Time(s)')
        self.gnt.set_ylabel('Tasks')

        # Setting graph attribute
        self.gnt.grid(True)

        if title:
            self.gnt.set_title(title)

        # Define available y position
        self.available_y = []
        index = 1
        while index < ylim:
            self.available_y.append((index, 2))
            index += 3

        # Initiate labels
        self.ylabels = [str(_) for _ in range(ylim)]
        self.gnt.set_yticks([_[0]+1 for _ in self.available_y])

        self.numberTasks = 0

    def addTask(self, name, runningPeriods):
        y_index = self.available_y[self.numberTasks]
        self.tasksColors[name] = np.random.rand(3,)
        self.tasksYticks[name] = y_index
        self.ylabels[self.numberTasks] = name
        self.gnt.set_yticklabels(labels=self.ylabels)
        self.numberTasks += 1
        self.gnt.broken_barh(
                runningPeriods, self.tasksYticks[name], facecolor=self.tasksColors[name])

    def show(self):
        plt.show()


def read_task_schedule_file(filename):
    f = open(filename, "r")
    lines = f.readlines()
    tasks_dict = dict()
    last_elem = "\n"
    rank = 0
    for elem in lines:
        if elem == '\n':
            rank += 1
            continue
        elem.replace('\n', '')
        if elem not in tasks_dict.keys():
            tasks_dict[elem] = []
        if last_elem == elem:
            tasks_dict[elem][-1][1] += 1
        else:
            tasks_dict[elem].append([rank, 1])
        last_elem = elem
        rank += 1
    
    for key in tasks_dict.keys():
        new_periods = []
        for period in tasks_dict[key]:
            new_periods.append((period[0], period[1]))
        tasks_dict[key] = new_periods
    return tasks_dict, len(lines)

def main():
    parser = argparse.ArgumentParser(description="Real-Time tasks Gantt plotter from data file")
    parser.add_argument('--filename', type=str, default='data/schedule', help='Register the path to the schedule description file')
    args = parser.parse_args()
    tasks_dict, hyperperiod = read_task_schedule_file(args.filename)

    gnt = GanttPlot(len(tasks_dict.keys())*3, hyperperiod, title="Real-Time Schedule")
    for key in tasks_dict.keys():
        gnt.addTask(key, tasks_dict[key])
    gnt.show()

if __name__ == "__main__":
    main()    