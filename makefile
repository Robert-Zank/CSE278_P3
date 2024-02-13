app: main.cpp CrewApp.o Flight.o Crew.o
	g++ main.cpp CrewApp.o Flight.o Crew.o -o app

CrewApp.o: CrewApp.cpp CrewApp.h
	g++ -c CrewApp.cpp -o CrewApp.o

Crew.o: Crew.cpp Crew.h
	g++ -c Crew.cpp -o Crew.o

Flight.o: Flight.cpp Flight.h
	g++ -c Flight.cpp -o Flight.o

run:
	./app CrewSchedule.txt Flights.txt

clean:
	rm *.o app
