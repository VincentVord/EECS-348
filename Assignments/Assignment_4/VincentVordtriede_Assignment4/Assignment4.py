#EECS 348 Assignment 4
#Boolean algebraic property solver using and object oriented approach
#Inputs: None - hardcoded
#Output: Truth tables for all boolean properties
#Collaborators: None
#Sources: ChatGPT
#Vincent Vordtriede
#10/6/2025

import itertools #import itertools for generate_table function

class BooleanSolver(): #defines the BooleanSolver Class
    def __init__(self, number, lhs, rhs, variables): #initialize all of the members of the class
        self.number = number #init the number (property number)
        self.lhs = lhs #init the LHS expression
        self.rhs = rhs #init the RHS expression
        self.variables = variables #init the list of included variables in each expression

    #I prompted ChatGPT to suggest this solution by asking how I could easily evaluate the expressions once generated
    def evaluate_expression(self, expr, assignment): #helper function that evaluates the boolean algebra expression
        local_dict = {v: bool(assignment[v]) for v in self.variables} #creates a dictionary that stores the variable name (key) and its corresponding boolean value (value)
        return int(eval(expr, local_dict)) #evaluates the boolean expression by using the mapping from local_dict to safely evaluate the expression -- and int() converts all booleans to their respective 0 or 1 countnerparts

    #ChatGPT suggested that I could use Python's itertools library, which easily allows the program to iterate through every combination of two numbers in a sequence
    def generate_table(self): #function that generates and prints the truth table
        print(f"\nBoolean Property {self.number}:") #print the property number
        print(f"LHS = {self.lhs}") #print the LHS
        print(f"RHS = {self.rhs}") #print the RHS
        header = "|".join(self.variables) + f"|{self.lhs}|{self.rhs}" #define the first line (the variables, LHS, and RHS)
        print(header) #print first line
        print("-" * len(header)) #print the separating line using len
        for combo in itertools.product([0, 1], repeat=len(self.variables)): #iterates over every possible combination of 0/1 assignments for the variables, repeating for the length of the variables list
            assignment = dict(zip(self.variables, combo)) #maps assignment to a tuple that is in the format: ()'variable', value) using zip. These are then converted to a dict

            lhs_val = self.evaluate_expression(self.lhs, assignment) #reassign LHS to the evaluated expression for the current assingment
            rhs_val = self.evaluate_expression(self.rhs, assignment) #reassign RHS to the evaluated expression for the current assingment

            lhs_padding = " "*int(((len(self.lhs))/2)) #generate whitespace based off of the length of the expression
            rhs_padding = " "*int(((len(self.rhs))/2)) #generate whitespace based off of the length of the expression

            row = "|".join(str(v) for v in combo) + f"|{lhs_padding}{lhs_val}{lhs_padding}|{rhs_padding}{rhs_val}{rhs_padding}" #for every combination of variable value assignments, print out the outputs separated by '|' (also while adding in the correct padding)
            print(row) #print the row


def parse(properties): #function that parses the initial property list
    parsed_properties = [] #create empty list
    for i in properties: #iterate through every property 
        if i.strip().startswith("4a") or i.strip().startswith("4b"): #handle special case for properties 4a and 4b
            if i.strip().startswith("4a"): #if the current property is 4a
                property = ["4a", "0", "not 0", []] #manually enter the LHS and RHS
            if i.strip().startswith("4b"): #if the current property is 4b
                property = ["4a", "1", "not 1", []] #manually enter the LHS and RHS
            parsed_properties.append(property) #add property to the final list
        else: #otherwise... do normal parsing
            number, expr = i.split(':') #assign number to everything before ':' and expr to everything after
            lhs, rhs = expr.split('=') #assign lhs to everything before '=' amd rhs to everything after
            lhs = convert_to_python(lhs.strip()) #convert all boolean operators to python operators
            rhs = convert_to_python(rhs.strip()) #convert all boolean operators to python operators
            
            variables = get_variables(lhs.strip()) #get the list of all included variables in the expression

            property = [number.strip(), lhs, rhs, variables] #create the property, which is a list containing the number, lhs, rhs, and list of variables
            parsed_properties.append(property) #add this property to the final list
    return parsed_properties #return list of lists Ex: [[number, lhs, rhs, (var1, var2,...)], [number2, lhs, rhs, (var1, var2,...)]]

def convert_to_python(expr): #converts all of the symbols to python boolean statements
    expr = expr.replace('·', ' and ') #replace · with and 
    expr = expr.replace('+', ' or ') #replace + with or
    expr = expr.replace('!', 'not ') #replace ! with not
    return expr #return modified expression

def get_variables(expr): #find all variables present in the current equation
    variables = set() #set cannot have duplicate
    for i in expr: #for every character in the expression
        if i=="x": #if x is in the expression
            variables.add(i) #add it (only once)
        elif i=="y": #if y is in the expression
            variables.add(i) #add it (only once)
        elif i=="z": #if z is in the expression
            variables.add(i) #add it (only once)
    var_list = list(variables) #convert back to a list when done, but items are in random set order
    
    if len(var_list)==0: #fix this by returning a fixed variable list depending on the length of the list
        return [] #empty string
    elif len(var_list)==1: #if the length is 1
        return ['x'] #only x is used
    elif len(var_list)==2: #if the length is 2
        return ['x','y'] #x and y are used
    elif len(var_list)==3: #if the length is 3
        return ['x','y','z'] #x, y and z are used

def main(): #defines the main function
    properties = [ #hard-coded list of properties from canvas assignment
        "1a: 0·0 = 0",
        "1b: 1+1 = 1",
        "2a: 1·1 = 1",
        "2b: 0+0 = 0",
        "3a: 0·1 = 1·0",
        "3b: 0+1 = 1+0",
        "4a: If x = 0, then !x = 1", 
        "4b: If x = 1, then !x = 0",
        "5a: x·0 = 0",
        "5b: x+1 = 1",
        "6a: x·1 = x",
        "6b: x+0 = x",
        "7a: x·x = x",
        "7b: x+x = x",
        "8a: x·!x = 0",
        "8b: x+!x = 1",
        "9: !!x = x",
        "10a: x·y = y·x",
        "10b: x+y = y+x",
        "11a: x·(y·z) = (x·y)·z",
        "11b: x+(y+z) = (x+y)+z",
        "12a: x·(y+z) = (x·y)+(x·z)",
        "12b: x+(y·z) = (x+y)·(x+z)",
        "13a: x+(x·y) = x",
        "13b: x·(x+y) = x",
        "14a: (x·y)+(x·!y) = x",
        "14b: (x+y)·(x+!y) = x",
        "15a: !(x·y) = !x+!y",
        "15b: !(x+y) = !x·!y",
        "16a: x+(!x·y) = x+y",
        "16b: x·(!x+y) = x·y",
        "17a: (x·y)+(y·z)+(!x·z) = (x·y)+(!x·z)",
        "17b: (x+y)·(y+z)·(!x+z) = (x+y)·(!x+z)"
    ]
    parsed = parse(properties) #parse the list of properties
    for i in parsed: #iterate through parsed list
        mysolver = BooleanSolver(i[0], i[1], i[2], i[3]) #create instance of class using the output list from parse()
        mysolver.generate_table() #print the table for each expression
main() #call main