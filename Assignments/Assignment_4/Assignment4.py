#EECS 348 Assignment 4
#
#Inputs: 
#Output: 
#Collaborators: 
#Sources: None
#Vincent Vordtriede
#10/6/2025

class BooleanSolver():
    def __init__(self, number, lhs, rhs, variables):
        self.number = number
        self.lhs = lhs
        self.rhs = rhs
        self.variables = variables
    
    def generate_table(self):
        print(f"Boolean Property {self.number}:")
        print(f"LHS = {self.lhs}")
        print(f"RHS = {self.rhs}")
        print(f"variables = {self.variables}")
        header = ""


def parse(properties):
    parsed_properties = []
    for i in properties:
        if i.strip().startswith("If"):
            continue
            #handle this case
        else:
            number, expr = i.split(':')
            lhs, rhs = expr.split('=')
            lhs = convert_to_python(lhs.strip())
            rhs = convert_to_python(rhs.strip())
            
            variables = get_variables(lhs.strip())

            property = [number.strip(), lhs, rhs, variables] 
            parsed_properties.append(property)
    return parsed_properties #return list of lists Ex: [[number, lhs, rhs], [number2, lhs, rhs]]

def convert_to_python(expr): #converts all of the symbols to python boolean statements
    expr = expr.replace('·', ' and ')
    expr = expr.replace('+', ' or ')
    expr = expr.replace('!', 'not ')
    return expr

def get_variables(expr): #find all variables present in the current equation
    variables = set() #cannot have duplicates
    for i in expr:
        if i=="x":
            variables.add(i)
        elif i=="y":
            variables.add(i)
        elif i=="z":
            variables.add(i)
    return list(variables) #convert to a list when done


def main():
    properties = [
        "1a: 0·0 = 0",
        "1b: 1+1 = 1",
        "2a: 1·1 = 1",
        "2b: 0+0 = 0",
        "3a: 0·1 = 1·0",
        "3b: 0+1 = 1+0",
        # "4a: If x = 0, then !x = 1", //strange formatting
        # "4b: If x = 1, then !x = 0",
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
    parsed = parse(properties)
    for i in parsed:
        mysolver = BooleanSolver(i[0], i[1], i[2], i[3])
        mysolver.generate_table()
        
    

main()