#include <iostream>
#include <cstring>

const int QUESTION_SIZE = 10;

// ANSWER ID
enum AnswerId {
    A = 1, // 1
    B,     // 2
    C,     // 3
    D      // 4
};

void initAnswerId(AnswerId& answerId) {
    char ch;
    std::cin >> ch;
    switch(ch) {
        case 'A': {
            answerId = AnswerId::A;
            break;
        }
        case 'B': {
            answerId = AnswerId::B;
            break;
        }
        case 'C': {
            answerId = AnswerId::C;
            break;
        }
        case 'D': {
            answerId = AnswerId::D;
            break;
        }
    }
}

char getAnswerId(const AnswerId id) {
    switch(id) {
        default:
        case AnswerId::A: {
            return 'A';
        }
        case AnswerId::B: {
            return 'B';
        }
        case AnswerId::C: {
            return 'C';
        }
        case AnswerId::D: {
            return 'D';
        }
    }
}

void printAnswerId(const AnswerId& id) {
    std::cout << getAnswerId(id);
}

// ANSWER
struct Answer {
    AnswerId id;
    char text[50 + 1]; // for '\0'
};

void initAnswer(Answer& answer, const AnswerId answerId) {
    answer.id = answerId;
    std::cin.getline(answer.text, 51);
}

void printAnswer(const Answer& answer) {
    printAnswerId(answer.id);
    std::cout << ": " << answer.text << std::endl;
}

// QUESTION
struct Question {
    char text[50+1]; // for '\0'
    Answer answers[4];
    AnswerId correctAnswer;
    int points;
};

void initQuestion(Question& question) {
    std::cin.getline(question.text, 51);

    for(int i = 0; i < 4; i++) {
        initAnswer(question.answers[i], (AnswerId)(i + 1));
    }

    initAnswerId(question.correctAnswer);
    std::cin >> question.points;
}

void printQuestion(const Question& question) {
    std::cout << "Q: ";
    std::cout << question.text << std::endl;
    std::cout << " --------- " << std::endl;

    for(int i = 0; i < 4; i++) {
        printAnswer(question.answers[i]);
    }
}

bool isCorrectAnswer(const Question& question, const AnswerId id) {
    return question.correctAnswer == id;
}

// TEST
struct Test {
    Question questions[QUESTION_SIZE];
};

void initTest(Test& test) {
    for(int i = 0; i < QUESTION_SIZE; i++) {
        initQuestion(test.questions[i]);
    }
}

int solveTest(const Test& test) {
    int totalPoints = 0;
    for(int i = 0; i < QUESTION_SIZE; i++) {
        printQuestion(test.questions[i]);

        AnswerId answer;
        initAnswer(answer);

        if(isCorrectAnswer(test.questions[i], answer)) {
            totalPoints += test.questions[i].points;
        }
    }
}
