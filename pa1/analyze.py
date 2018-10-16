import matplotlib.pyplot as plt
import numpy as np

plt.plot([1362, 9216, 82360, 185462], [0.021758, 0.468641, 31.103, 164.059], color='red', linestyle='--', label='Inserion Sort')
plt.plot([1362, 9216, 82360, 185462], [0.010448, 0.051509, 0.447067, 1.0113], color='blue', linestyle=':', label='Merge Sort')
plt.plot([1362, 9216, 82360, 185462], [0.00710, 0.044702, 0.399428, 0.917357], color='green',label='Heap Sort')
plt.plot([1362, 9216, 82360, 185462], [0.007151, 0.04363, 0.363662, 0.851294], color='black', linestyle='-.', label='Quick Sort')

plt.ylabel('CPU time (sec)')
plt.xlabel('number of words')

'''
plt.plot([1362, 9216, 82360, 185462], [0.2109, 1.133, 10.66, 26.09], color='red', linestyle='--', label='Inserion Sort')
plt.plot([1362, 9216, 82360, 185462], [0.2383, 1.641 , 11.73, 25.76], color='blue', linestyle=':', label='Merge Sort')
plt.plot([1362, 9216, 82360, 185462], [0.207, 1.129, 9.078, 19.52], color='green', label='Heap Sort')
plt.plot([1362, 9216, 82360, 185462], [0.1875, 1.133, 9.086, 19.54], color='black', linestyle='-.', label='Quick Sort')

plt.ylabel('Memory (MB)')
plt.xlabel('number of words')
'''
plt.legend(loc='upper right')
plt.show()
plt.savefig('memory.png')