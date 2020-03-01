from Polygon import Polygon

def main():
    list_x = [8, 10, 12, 13, 10, 8]
    list_y = [2, 4, 2, 8, 7, 8]

    polygon = Polygon(list_x, list_y)
    Polygon.check_if_exist(polygon)

if __name__ == '__main__':
    main()