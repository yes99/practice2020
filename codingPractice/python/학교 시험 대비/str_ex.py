n=500
m="Good Morning !! "
print("="*15)
print("상품개수는: %d"%n)
print("상품개수는: %5d"%n)  #  500
print("상품개수는: %05d"%n) #00500
print("%s.상품개수는:%f"%(m,n))
print("%20s.상품개수는:%9f"%(m,n))
print("%-20s.상품개수는:%8.2f"%(m,n))

"""
Good Morning !! .상품개수는:500.000000
    Good Morning !! .상품개수는:500.000000
Good Morning !!     .상품개수는:  500.00
"""
