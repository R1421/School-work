#This is to test the parsing code
my_list = [1,2,3,4,5,6,7]
print(len(my_list))
print('The entry in the list is: %d\n'*len(my_list) %tuple(my_list))

my_dict = {1:'orange', 2:'green', 3:'blue'}
my_list = []
for i in my_dict:
    my_list += [i]
    my_list += [my_dict[i]]
    print(my_list)

print(my_list)
print('The entry in the list is: %s\n'*len(my_list) %tuple(my_list))
print('%s %s  '*int((len(my_list)/2)) %tuple(my_list))
