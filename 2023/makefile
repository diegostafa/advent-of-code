flags=-std=c++20 -O3 -march=native
buildDir=build
exe=a.out

clean:
	rm -r $(buildDir)

run:
	@mkdir $(buildDir)
	@g++ $(flags) src/day-$(day)/$(part).cpp -o $(buildDir)/$(exe)
	@./$(buildDir)/$(exe)
