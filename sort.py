def sortFile(src, dst):
	s, d = open(src, 'r'), open(dst, 'w')
	l, temp = s.readline(), list()
	while len(l) > 0:
		temp.append(l)
		l = s.readline()
	temp.sort()
	d.write(''.join(temp))
	s.close(); d.close()

sortFile("LetItBe.txt", "sort.txt")
