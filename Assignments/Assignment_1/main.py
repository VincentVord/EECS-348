#have to organize by priority in a priority queue (5 being most priority)
#Boss == 5
#Subordinate == 4
#Peer == 3
#ImportantPerson == 2
#OtherPerson == 1
#if two emails are from the same sender, prioritize the one that was sent first

##fix dates not comparing correctly

from maxheap import MaxHeap
from email import Email

PriorityQueue = MaxHeap() #create instance of a MaxHeap

def main():
    user_file = 'Assignment1_Test_File.txt'

    with open(user_file, 'r') as file: #opens the file and extracts each piece of information 
        for line in file:
            line = line.strip()
            if line.startswith("EMAIL"):
                temp = line.split(' ', 1)[1]
                data = temp.split(",")
                sender_category = data[0]
                subject_line = data[1]
                date = data[2]
                email = Email(sender_category, subject_line,date) #create instance of an email
                PriorityQueue.add(email)

                print(data)
                print (email.priority_number)
                print(PriorityQueue._heap)

            elif line == "COUNT":
                print(f"There are {PriorityQueue.count()} emails to read.\n") #prints the amount of emails unread
            elif line == "NEXT":
                if PriorityQueue.count() > 0:
                    next_email = PriorityQueue._heap[0]
                    print(f"Next email:\n{next_email}\n") #prints the next email
                else:
                    print("No emails to read.\n") #handles no emails case
            elif line == "READ":
                if PriorityQueue.count() > 0:
                    PriorityQueue.remove() #removes the email from the heap
                else:
                    print("No emails to read.\n") #handles no emails case
main()