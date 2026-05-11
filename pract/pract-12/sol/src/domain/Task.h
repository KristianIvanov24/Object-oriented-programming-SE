#pragma once
#include "Date.h"
#include "Priority.h"
#include "Status.h"
#include <string>

class Task
{
protected:
    static int nextId;
    int id;
    std::string title;
    std::string description;
    Date deadline;
    Priority priority;
    Status status;

public:
    Task(
        const std::string& title,
        const std::string& description,
        const Date& deadline,
        Priority priority);

    virtual ~Task() = default;

    virtual void complete() = 0;

    int getId() const;
    const std::string& getTitle() const;
    const std::string& getDescription() const;
    const Date& getDeadline() const;
    Priority getPriority() const;
    Status getStatus() const;

    bool isOverdue() const;
    bool isCompleted() const;

    void setStatus(Status status);

private:
    void setTitle(const std::string& title);
    void setDescription(const std::string& description);
};
