#include "TaskValidation.h"
#include "Validation.h"
#include "constants/TaskResources.h"

bool TaskValidation::isValidTitle(const std::string& title)
{
    return Validation::inRange(
        title.size(),
        resources::task::MIN_TITLE_LENGTH,
        resources::task::MAX_TITLE_LENGTH);
}

bool TaskValidation::isValidDescription(const std::string& description)
{
    return Validation::inRange(
        description.size(),
        resources::task::MIN_DESCRIPTION_LENGTH,
        resources::task::MAX_DESCRIPTION_LENGTH);
}
