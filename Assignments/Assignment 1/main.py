#have to organize by priority in a priority queue (5 being most priority)
#Boss == 5
#Subordinate == 4
#Peer == 3
#ImportantPerson == 2
#OtherPerson == 1
#if two emails are from the same sender, prioritize the one that was sent first

#To do next:
#figure out how to compare/extract dates
#make sure the __lt__ magic method works
#Add test files and debug


from maxheap import MaxHeap
from email import Email

PriorityQueue = MaxHeap()

def main():
    user_file = input("Enter the name of your email file: ")

    with open(user_file, 'r', encoding="utf8") as file: #opens the file and extracts each piece of information 
        for line in file:
            line = line.strip()
            if line.startswith("EMAIL"):
                data = line.split()
                command = data[0]
                sender_category = data[1]
                subject_line = data[2]
                date = data[3]
                email = Email(sender_category, subject_line,date) #create instance of an email
                PriorityQueue.add(email)
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