#include "Controller.hpp"

int Controller::buttonCheck()
{
    int button = Window::input();
    auto selectedPosition = board.selected;

    switch (button)
    {
    case Keys::Up:
        if (selectedPosition.x - 1 >= 0)
            selectedPosition.x -= 1;
        break;
    case Keys::Down:
        if (selectedPosition.x + 1 < (int)board.getBoard().size() - 1)
            selectedPosition.x += 1;
        break;
    case Keys::Left:
        if (selectedPosition.y - 1 >= 0)
            selectedPosition.y -= 1;
        break;
    case Keys::Right:
        if (selectedPosition.y + 1 < (int)board.getBoard()[0].size() - 1)
            selectedPosition.y += 1;
        break;
    case Keys::Esc:
        playQuit = true;
        break;
    case Keys::Enter:
        board.rotateSelected();
        break;
    }

    board.selected = selectedPosition;

    return 0;
}

void Controller::play()
{
    board.init(level);
    playQuit = false;
    std::time_t startTime = std::time(0);

    const int seconds = 30 * (timer + 1);
    int score = seconds * 5;
    bool won = false;

    while (!playQuit)
    {
        win.drawBoard();
        int elapsedSeconds = std::difftime(std::time(0), startTime);
        win.drawTime(seconds - elapsedSeconds);
        won = board.checkWater();
        if (seconds - elapsedSeconds <= 0 || won)
        {
            break;
        }
        score -= 5;
        buttonCheck();
    }
    
    if (won)
    {
        if (score > 0)
        {
            FileSystem::Info records = FileSystem::read("records.txt");
            records.push_back(score);
            std::sort(records.begin(), records.end());
            FileSystem::write(records, "records.txt");
        }
        win.drawTextWin("Win");
    }
    else
    {
        win.cleanWindow();
        win.drawText("Game over");
    }
    win.input();
    win.input();
    board.clear();
}

void Controller::menu()
{
    std::vector<std::string> sections = {"Play", "Options", "Records", "Exit"};
    int selected = 0;
    bool quit = false;
    while (!quit)
    {
        win.drawMenu(sections, selected);
        switch (Window::input())
        {
        case Keys::Up:
            if (selected > 0)
                --selected;
            break;
        case Keys::Down:
            if (selected < (int)sections.size() - 1)
                ++selected;
            break;
        case Keys::Enter:
            if (sections[selected] == "Play")
                play();
            else if (sections[selected] == "Records")
                records();
            else if (sections[selected] == "Options")
                options();
            else if (sections[selected] == "Exit")
                quit = true;
        }
    }
}

void Controller::options()
{
    std::vector<std::string> sections = {"Level 1", "Level 2", "Level 3", "Level 4","-------", "Time 30s", "Time 60s", "Back"};
    sections[level] += " <";
    int levelsCount = 4;
    sections[levelsCount + timer + 1] += " <";
    int selected = 0;
    bool quit = false;
    
    while (!quit)
    {
        win.drawMenu(sections, selected);
        switch (Window::input())
        {
        case Keys::Up:
            if (selected > 0)
                --selected;
            break;
        case Keys::Down:
            if (selected < (int)sections.size() - 1)
                ++selected;
            break;
        case Keys::Enter:
            if (sections[selected] == "Level 1")
            {
                sections[level] = sections[level].substr(0, sections[level].size() - 2);
                sections[selected] = "Level 1 <";
                level = 0;
            }
            else if (sections[selected] == "Level 2")
            {
                sections[level] = sections[level].substr(0, sections[level].size() - 2);
                sections[selected] = "Level 2 <";
                level = 1;
            }
            else if (sections[selected] == "Level 3")
            {
                sections[level] = sections[level].substr(0, sections[level].size() - 2);
                sections[selected] = "Level 3 <";
                level = 2;
            }
            else if (sections[selected] == "Level 4")
            {
                sections[level] = sections[level].substr(0, sections[level].size() - 2);
                sections[selected] = "Level 4 <";
                level = 3;
            }
            else if (sections[selected] == "Time 30s")
            {
                sections[levelsCount + 1 + timer] = sections[levelsCount + 1 + timer].substr(0, sections[levelsCount + 1 + timer].size() - 2);
                sections[selected] = "Time 30s <";
                timer = 0;
            }
            else if (sections[selected] == "Time 60s")
            {
                sections[levelsCount + 1 + timer] = sections[levelsCount + 1 + timer].substr(0, sections[levelsCount + 1 + timer].size() - 2);
                sections[selected] = "Time 60s <";
                timer = 1;
            }
            else if (sections[selected] == "Back")
                quit = true;
        }
    }
}

void Controller::records()
{
    std::vector<std::string> sections;
    FileSystem::Info fileContent = FileSystem::read("records.txt");
    std::reverse(fileContent.begin(), fileContent.end());   

    for (int i = 0; i < (int)fileContent.size(); ++i)
    {
        if (i == 12) break;
        sections.push_back(std::to_string(i + 1) + ") " + std::to_string(fileContent[i]));
    }

    sections.push_back("Back");
    int selected = 0;
    bool quit = false;
    
    while (!quit)
    {
        win.drawMenu(sections, selected);
        switch (Window::input())
        {
        case Keys::Up:
            if (selected > 0)
                --selected;
            break;
        case Keys::Down:
            if (selected < (int)sections.size() - 1)
                ++selected;
            break;
        case Keys::Enter:
            if (sections[selected] == "Back")
                quit = true;
        }
    }
}
