#EECS 348 Assignment 1
#Email Priority queue using a Maxheap with a list-based implementation
#Inputs: test file labeled Assignment1_Test_File.txt
#Output: Next email and number of unread emails
#Collaborators: None
#EECS 268 material, StackOverflow, ChatGPT
#Vincent Vordtriede
#8/26/2025


class MaxHeap: #my maxheap class from EECS 268
    def __init__(self): #initializes the maxheap class
        self._heap = [] #empty list for a list based implementation
    
    def count(self): #defines the count method 
        return len(self._heap) #returns the length of the heap list

    def add(self,entry): #defines the add method
        self._heap.append(entry) #add new element to the heap
        self._upheap(len(self._heap)-1) #upheap starting at the last index in the list

    def _upheap(self, index): #defines the private upheap function
        if index == 0: #if at the root, do nothing
            return
        parent = (index - 1) // 2 #define maxheap list equation for the parent node
        if self._heap[parent] < self._heap[index]: # Swap and continue upheap
            self._heap[parent], self._heap[index] = self._heap[index], self._heap[parent] #swap the current index with the parent
            self._upheap(parent) #recursively upheap again until you cannot anymore

    def remove(self): # defines the remove method 
        if len(self._heap)>0: #if the heap is not empty
            root_value = self._heap[0] #set the root as the first index in the list
            self._heap[0] = self._heap[-1] #assign the last entry in the heap to the root
            self._heap.pop(-1) #remove that last entry
            self._downheap(0) #downheap starting at the new root
            return root_value #return the value of the new root
        else:
            raise RuntimeError('Heap empty') #handles empty heap case
    
    def _downheap(self, index): #defines the private downheap function
        child_index = 2 * index + 1 #defines the maxheap list equation for the child node
        if child_index >= len(self._heap): #if the child index is out of bounds, do nothing
            return
        if child_index + 1 < len(self._heap) and self._heap[child_index] < self._heap[child_index + 1]: # Choose the larger child to swap with
            child_index += 1 #increment the child index to the next item in the list
        if self._heap[index] < self._heap[child_index]: # Now use this child's index to swap and continue downheap
            self._heap[index], self._heap[child_index] = self._heap[child_index], self._heap[index] #swap child and current index
            self._downheap(child_index) #recursively downheap child index


class Email: #deines the Email class
    def __init__(self, sender_category, subject_line, date): #initializes the sender, subject, and date
        self.subject_line = subject_line #defines subject_line
        self.date = date #defines date

        m, d, y = date.split("-") #got this syntax from ChatGPT to easily reformat the date by splitting the date by '-' and immediately assinging m, d, and y at the same time
        self.formatted_date = y + m + d # for comparing dates easily (YYYYMMDD)

        self.sender_category = sender_category #defines sender_category
        
        if self.sender_category == "Boss":               #categorize each sender by number to easily compare
            self.priority_number = 5                     #the priority of each sender type. Boss is assigned 5,
        elif self.sender_category == "Subordinate":      #Subordinate is assigned 4, Peer is assigned 3,
            self.priority_number = 4                     #ImportantPerson is assigned 2, and OtherPerson is
        elif self.sender_category == "Peer":             #assigned 1.
            self.priority_number = 3
        elif self.sender_category == "ImportantPerson":
            self.priority_number = 2
        elif self.sender_category == "OtherPerson":
            self.priority_number = 1
    
    def __lt__(self,other): #defines less than magic method for when the maxheap class has to compare class objects
        if self.priority_number != other.priority_number: #if the priority numbers are not the same...
            return self.priority_number < other.priority_number #prioritize by lowest priority_number
        else: #otherwise...
            return self.formatted_date < other.formatted_date #if the sender is the same prioritize by most recent date
    
    def __str__(self): #defines the string magic method for when main has to print class objects
        return (f"\tSender: {self.sender_category}\n" #prints the email information in a well-formatted manor
                f"\tSubject: {self.subject_line}\n"
                f"\tDate: {self.date}\n")



PriorityQueue = MaxHeap() #create instance of a MaxHeap

def main(): #defines the main function
    user_file = 'Assignment1_Test_File.txt' #Name of the given test file from the Assignment

    with open(user_file, 'r') as file: #opens the file and extracts each piece of information 
        for line in file: #for every line in the input file
            line = line.strip() #strip the whitespace (gets rid of newlines)

            if line.startswith("EMAIL"): #check if the line starts with the EMAIL command
                temp = line.split(' ', 1)[1] #first split the line by a space only after the first word (separating 'EMAIL' from the rest of the line)
                data = temp.split(",") #next split by commas to get the remaining information into a list with 3 indices

                sender_category = data[0] #the first index is defined as the sender
                subject_line = data[1] #the second index is defined as the subject
                date = data[2] #the third index is defined as the date

                email = Email(sender_category, subject_line,date) #create instance of an email using the extracted data
                PriorityQueue.add(email) #add the email to the priority queue

            elif line == "COUNT": #check if the command is COUNT
                print(f"There are {PriorityQueue.count()} emails to read.\n") #prints the amount of emails unread

            elif line == "NEXT": #check if the command is NEXT
                if PriorityQueue.count() > 0: #check if the maxheap is not empty
                    next_email = PriorityQueue._heap[0] #grabs the next email by looking at the root
                    print(f"Next email:\n{next_email}\n") #prints the next email
                else: #otherwise...
                    print("No emails to read.\n") #handles no emails case

            elif line == "READ": #check if the command is READ
                if PriorityQueue.count() > 0: #check if the maxheap is not empty
                    PriorityQueue.remove() #removes the email from the heap
                else: #otherwise...
                    print("No emails to read.\n") #handles no emails case

main() #calls the main function