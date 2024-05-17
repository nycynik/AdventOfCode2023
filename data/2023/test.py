from itertools import permutations
import re

with open("day7_input.txt",'r',encoding="utf-8") as f:
    input = f.read()
#mapping
#TJQKA
#:;<=>
#:1<=> for p2
def fix_input(part):
    jreplace = ";" if part==1 else "1"
    out = input.replace("T",":").replace("J",jreplace)\
    .replace("Q","<").replace("K","=").replace("A",">")\
    .split("\n")
    return out

def determine_rank_1(card):
    s=set(card)
    #5 of a kind / high card
    if len(s)==1:
        return 7
    if len(s)==5:
        return 1
    d={}
    for token in card:
        if token not in d:
            d[token]=1
            continue
        d[token]+=1
    v=list(d.values())
    v.sort()
    match v:
        case [1,1,1,2]:
            #pair
            return 2
        case [1,2,2]:
            # two pair
            return 3
        case [1,1,3]:
            #3 of a kind
            return 4
        case [2,3]:
            #full house
            return 5
    return 6 #4 oak

def multireplace(str,targets,token):
    for target in targets:
        str = str.replace(token,target,1)
    return str

def determine_rank_2(card):
    opts = [str(x) for x in range(2,10)]\
        + [":","<",'=',">"]
    jcount = len(re.findall("1",card))
    perms=(permutations(opts*jcount,jcount))
    max=1
    for perm in perms:
        newcard = multireplace(card,perm,"1")
        r=determine_rank_1(newcard)
        if r==7:
            return r
        if r>max:
            max=r
    return max
def run(part):
    buckets={1:[],2:[],3:[],4:[],5:[],6:[],7:[]}
    rank_f = determine_rank_1 if part==1 else determine_rank_2
    entries=fix_input(part)
    for card in entries:
        c,_ = card.split(" ")
        buckets[rank_f(c)].append(card)

    def process_bucket(bucket,init):
        counter = init
        bucket.sort()
        partial_sum=0
        for item in bucket:
            _,val=item.split(" ")
            val=int(val)
            partial_sum+=counter*val
            counter+=1
        return partial_sum,counter
    c=1
    sum=0
    for i in range(1,8):
        s,c=process_bucket(buckets[i],c)
        sum+=s

    print(sum)

run(1)
run(2)