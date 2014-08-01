import json
import glob

def GetDistances(myfile):

    data=myfile.read()
    j = json.loads(data)
    a=[]
    for l in j["rows"][0]["elements"]: a.append(l["distance"]["value"])
    return a

distances = []
for name in sorted(glob.glob("*.json")):
    #print(name)
    a = GetDistances(open(name))
    #print(a)
    distances.append(a)

matrix = open("matrix.dat",'w')
matrix.write(str(distances).replace('[','\n').replace(',','').replace(']',''))
