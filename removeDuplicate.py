def uniqueFile(src, dst):
	s, d = open(src, 'r'), open(dst, 'w')
	l, prevL = s.readline(), ''
	while len(l) > 0:
		if l != prevL:
			d.write(l)
		prevL, l = l, s.readline()
	s.close(); d.close()

uniqueFile("LetItBe.txt", "duplicate.txt")
