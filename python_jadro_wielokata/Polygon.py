class Polygon:

    def __init__(self, list_x, list_y):
        self.list_x = list_x
        self.list_y = list_y
        self.max_local = None
        self.min_local = None

    def check_turning_direction(self, point_index):
        i = point_index

        list_x = self.list_x
        list_y = self.list_y

        if i == 0:
            x0 = list_x[len(list_x) - 1]
            y0 = list_y[len(list_y) - 1]
            x1 = list_x[i]
            x2 = list_x[i + 1]
            y1 = list_y[i]
            y2 = list_y[i + 1]
        elif i == len(list_x) - 1:
            x2 = list_x[0]
            y2 = list_y[0]
            x0 = list_x[i - 1]
            x1 = list_x[i]
            y0 = list_y[i - 1]
            y1 = list_y[i]
        else:
            x0 = list_x[i - 1]
            x1 = list_x[i]
            x2 = list_x[i + 1]
            y0 = list_y[i - 1]
            y1 = list_y[i]
            y2 = list_y[i + 1]


        compute = ((x2 - x0) * (y1 - y0)) - ((x1 - x0)*(y2 - y0))

        if compute > 0 and y0 > y1 and y1 < y2:
            # z pkt idziemy w prawo, w gore osi y
            return -1
        elif compute > 0 and y0 < y1 and y1 > y2:
            #z pkt idziemy w prawo, w dol osi y
            return 1

        #obsluga "zebow"
        if compute > 0 and y0 < y1 and y1 == y2:
            return 2
        elif compute > 0 and y0 > y1 and y1 == y2:
            return -2

        return 0


    def get_min_and_max_local(self):
        list_x = self.list_x
        list_y = self.list_y

        list_max_local = []
        list_min_local = []

        for i in range(0, len(list_y)):
            if self.check_turning_direction(i) == 1:
                list_max_local.append(list_y[i])
            elif self.check_turning_direction(i) == -1:
                list_min_local.append(list_y[i])

            if self.check_turning_direction(i) == 2:
                for j in range(i, len(list_y)):
                    if list_y[j] < list_y[i] and list_x[j] > list_x[i] and self.check_turning_direction(j) == 0:
                        list_max_local.append(list_y[i])
                        break
            elif self.check_turning_direction(i) == -2:
                for j in range(i, len(list_y)):
                    if list_y[j] > list_y[i] and list_x[j] < list_x[i] and self.check_turning_direction(j) == 0:
                        list_min_local.append(list_y[i])
                        break

        if len(list_max_local) == 0:
            list_min_local = list_y
            result_max = min(list_min_local)
        else:
            result_max = max(list_max_local)

        if len(list_min_local) == 0:
            list_min_local = list_y
            result_min = max(list_min_local)
        else:
            result_min = min(list_min_local)

        self.max_local = result_max
        self.min_local = result_min

        return


    def check_if_exist(self):
        self.get_min_and_max_local()
        print("Max local: ", self.max_local)
        print("Min local: ", self.min_local)
        print(self.min_local >= self.max_local)
