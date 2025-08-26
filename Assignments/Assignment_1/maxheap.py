class MaxHeap: #maxheap class from EECS 268
    def __init__(self):
        self._heap = [] #empy list for a list based implementation
    
    def count(self):
        return len(self._heap)

    def add(self,entry): #add new element to the heap
        self._heap.append(entry)
        self._upheap(len(self._heap)-1) #upheap starting at the last index in the list

    def _upheap(self, index):
        if index == 0:
            return
        parent = (index - 1) // 2
        if self._heap[parent] < self._heap[index]: # Swap and continue upheap
            self._heap[parent], self._heap[index] = self._heap[index], self._heap[parent]
            self._upheap(parent)

    def remove(self): #remove from the maxheap (the root element)
        if len(self._heap)>0:
            root_value = self._heap[0]
            self._heap[0] = self._heap[-1] #assign the last entry in the heap to the root
            self._heap.pop(-1) #remove that last entry
            self._downheap(0) #downheap starting at the new root
            return root_value
        else:
            raise RuntimeError('Heap empty')
    
    def _downheap(self, index):# Check that we stay within the bounds of the heap
        child_index = 2 * index + 1
        if child_index >= len(self._heap):
            return
        elif child_index + 1 < len(self._heap) and self._heap[child_index] < self._heap[child_index + 1]: # Choose the larger child to swap with
            child_index += 1
        elif self._heap[index] < self._heap[child_index]: # Now use this child's index to swap and continue downheap
            self._heap[index], self._heap[child_index] = self._heap[child_index], self._heap[index]
            self._downheap(child_index)