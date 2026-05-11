#include "repositories/TaskRepository.h"
#include "services/TaskService.h"
#include "ui/ConsoleUI.h"

int main() {
    TaskRepository repository("whatev.dat");
    repository.loadFromFile();

    TaskService service(repository);

    ConsoleUI ui(service);
    ui.run();

    repository.saveToFile();
    return 0;
}