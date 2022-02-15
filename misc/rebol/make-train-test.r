rebol []

;Install Mac 	wget https://github.com/nicolas42/rebol/blob/master/mac/rebol
;Install Linux 	wget https://github.com/nicolas42/rebol/blob/master/linux/rebol

dir: %dataset/  
f: read dir  
remove-each f f [ %.jpg <> suffix? f ]  

random/seed now/precise
f: random f

forall f [ insert f/1 dir ]  
train: take/part f to-integer 0.7 * length? f
test: f

print train
print test

write/lines %train.txt train
write/lines %test.txt test
