backend?=g++
flags=-std=c++20 -O3 -march=native -pthread
buildDir=build
exe=a.out

clean:
	rm -r $(buildDir)

run:
	@reset
	@mkdir -p $(buildDir)
	@$(backend) $(flags) src/day-$(day)/$(part).cpp -o $(buildDir)/$(exe)
	./$(buildDir)/$(exe)

new:
	@mkdir -p src/day-$(day)
	@touch src/day-$(day)/input.txt
	@touch src/day-$(day)/silver.cpp
	@touch src/day-$(day)/gold.cpp
	@cat templates/silver.txt > src/day-$(day)/silver.cpp