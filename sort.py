import time
import matplotlib.pyplot as plot 
import random

NDis = 100
NBen = 5000
BENCHMARK = True

def init_tab(n):
	tab = []
	for i in range(0,n):
		tab.append(random.random())
		# tab.append(n-i)
	# tab[0], tab[n-1] = tab[n-1], tab[0]
	# random.shuffle(tab)
	return tab

def plot_tab(tab, title):
	plot.title(title)
	plot.plot(tab, 'r.')
	plot.draw()
	plot.pause(0.001)
	plot.clf()

def bubble_sort(tab):
	sorted = False
	j = 0
	i = len(tab) - 1
	while (i > 0 and not(sorted)):
		sorted = True
		for j in range(0,i):
			if (tab[j] > tab[j+1]):
				tab[j], tab[j+1] = tab[j+1], tab[j]
				sorted = False
		if not BENCHMARK:
			plot_tab(tab, 'Bubble Sort')
		i = i - 1

def insertion_sort(tab):
	for i in range(1,len(tab)):
		x = tab[i]
		j = i
		while (j > 0 and tab[j-1] > x):
			tab[j] = tab[j-1]
			j = j-1
		tab[j] = x
		if not BENCHMARK:
			plot_tab(tab, 'Insertion Sort')

def cocktail_shaker_sort(tab):
	start = 0
	swaped = True
	end = len(tab)-2
	while (swaped):
		swaped = False
		for i in range(start,end+1):
			if (tab[i] > tab[i+1]):
				tab[i], tab[i+1] = tab[i+1], tab[i]
				swaped = True
		end = end - 1
		for i in range(end, start-1, -1):
			if (tab[i] > tab[i+1]):
				tab[i], tab[i+1] = tab[i+1], tab[i]
				swaped = True
		start = start + 1
		if not BENCHMARK:
			plot_tab(tab, 'Cocktail Shaker Sort')

def odd_even_transposition_sort(tab):
	sorted = False
	while (not sorted):
		sorted = True
		for i in range(1,len(tab)-1,2):
			if (tab[i] > tab[i+1]):
				tab[i], tab[i+1] = tab[i+1], tab[i]
				sorted = False
		for i in range(0,len(tab)-1,2):
			if (tab[i] > tab[i+1]):
				tab[i], tab[i+1] = tab[i+1], tab[i]
				sorted = False
		if not BENCHMARK:
			plot_tab(tab, 'Odd-Even Transposition Sort')

def topDownMergeSort(A):
	B = A.copy()
	topDownSplitMerge(B, 0, len(A), A)

def topDownSplitMerge(B, iBegin, iEnd, A):
	if ((iEnd - iBegin) < 2):
		return
	iMiddle = int((iEnd + iBegin) / 2)
	topDownSplitMerge(A, iBegin, iMiddle, B)
	topDownSplitMerge(A, iMiddle, iEnd, B)
	topDownMerge(B, iBegin, iMiddle, iEnd, A)
	if not BENCHMARK:
		plot_tab(A, 'Merge Sort')

def topDownMerge(A, iBegin, iMiddle, iEnd, B):
	i = iBegin
	j = iMiddle
	for k in range(iBegin,iEnd):
		if (i < iMiddle and (j >= iEnd or A[i] <= A[j])):
			B[k] = A[i]
			i = i + 1
		else:
			B[k] = A[j]
			j = j + 1

def Display():
	print('DISPLAY PHASE: ' + str(NDis) + ' Values\n')
	global BENCHMARK
	BENCHMARK = False
	random.seed()
	plot.ion()
	tabBackup = init_tab(NDis)
	tab = tabBackup.copy()
	print('Executing insertion sort.')
	insertion_sort(tab)
	tab = tabBackup.copy()
	print('Executing Bubble sort.')
	bubble_sort(tab)
	tab = tabBackup.copy()
	print('Executing Cocktail Shaker sort.')
	cocktail_shaker_sort(tab)
	tab = tabBackup.copy()
	print('Executing Odd-Even Transposition sort')
	odd_even_transposition_sort(tab)
	tab = tabBackup.copy()
	print('Executing Merge sort.')
	topDownMergeSort(tab)
	plot.close()
	plot.ioff()

def Benchmak():
	print('BENCHMARK PHASE: ' + str(NBen) + ' Values\n')
	print('Sorting Algorithm            Time (s)')
	print('----------------------------------------------')
	global BENCHMARK
	BENCHMARK = True
	tabBackup = init_tab(NBen)
	times = []

	tab = tabBackup.copy()
	start = time.time()
	insertion_sort(tab)
	end = time.time()
	print("Insertion Sort:             ", end-start)
	times.append(end-start)

	tab = tabBackup.copy()
	start = time.time()
	bubble_sort(tab)
	end = time.time()
	print("Bubble Sort:                ", end-start)
	times.append(end-start)

	tab = tabBackup.copy()
	start = time.time()
	cocktail_shaker_sort(tab)
	end = time.time()
	print("Cocktail Shaker Sort:       ", end-start)
	times.append(end-start)

	tab = tabBackup.copy()
	start = time.time()
	odd_even_transposition_sort(tab)
	end = time.time()
	print("Odd-Even Transposition Sort:", end-start)
	times.append(end-start)

	tab = tabBackup.copy()
	start = time.time()
	topDownMergeSort(tab)
	end = time.time()
	print("Merge Sort:                 ", end-start)
	times.append(end-start)

	tab = tabBackup.copy()
	start = time.time()
	tab.sort()
	end = time.time()
	print("Python Sort:                ", end-start)
	times.append(end-start)

	plot.title('Benchmak')
	plot.ylabel('Time (s)')
	plot.xlabel('Sorting Algorithm')
	plot.grid()
	plot.plot(['Insertion','Bubble','Cocktail','Odd-Even','Merge','Python'], times, 'rx')
	plot.show()

Display()
print()
Benchmak()