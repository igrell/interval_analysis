from matplotlib import pyplot as plt
import ast

def parse_rectangles(data_directory):
    data = open(data_directory, "r").read()
    rectangles = []
    for rectangle in data.split('\n'):
        if rectangle == '':
            break
        rectangles.append(ast.literal_eval(rectangle))
    return rectangles

def plot_rectangles(rectangles):
    ax = plt.gca()
    for rectangle in rectangles:
        ax.fill_between(x=rectangle[0], y1=(rectangle[1][1], rectangle[1][1]), y2=(rectangle[1][0], rectangle[1][0]), color="blue", alpha=0.1)
    plt.show()

if __name__ == '__main__':
    rectangles = parse_rectangles("/home/igor/Documents/Kod/Tutorial/Validated_numerics/interval_analysis/cmake-build-debug/output.txt")
    # rectangles = parse_rectangles(sys.argv)
    plot_rectangles(rectangles)