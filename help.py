# small helper script
# taken from wireshark

ismaster_bytes = "3a0000000600000000000000dd0700000000000000250000000169734d617374657200000000000000f03f022464620005000000746573740000"

out = []
for i in range(len(ismaster_bytes) // 2):
    out.append("0x" + ismaster_bytes[i*2:i*2 + 2])

first = True
print("{", end="")
for x in out:
    if not first:
        print(",", end="")
    first = False   
    print(x, end="")

print("}")