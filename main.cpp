#include <iostream>
#include <sstream>
#include "RecordsCollection.h"
#include <cassert>
#include <fstream>

bool compareStudents(const Student &oneStudent, const Student &secondStudent) {
    return (oneStudent.course == secondStudent.course &&
            oneStudent.firstName == secondStudent.firstName &&
            oneStudent.lastName == secondStudent.lastName &&
            oneStudent.middleName == secondStudent.middleName);
}

bool compareDates(const std::string &oneDate, const std::string &secondDate) {
    return (oneDate == secondDate);
}

bool compareWateringVolume(const float &oneWateringVolume,
                           const float &secondWateringVolume) {
    return (oneWateringVolume == secondWateringVolume);
}

bool compareWateringRecord(WateringRecord &first, WateringRecord &second) {
    return (compareStudents(first.getStudent(), second.getStudent()) &&
            compareDates(first.getDate(), second.getDate()) &&
            compareWateringVolume(first.getRecordValue(),
                                  second.getRecordValue()));
}

// test construction
WateringRecord
testWateringRecordConstruction(std::string &initialDate,
                               std::string &initialFisrtName,
                               std::string &initialMiddleName,
                               std::string &initialLastName,
                               std::string &initialCourse,
                               float initialWateringVolume) {
    WateringRecord testRecord(initialDate,
                              initialFisrtName,
                              initialMiddleName,
                              initialLastName,
                              initialCourse,
                              initialWateringVolume);
    return testRecord;
}

void testCopyConstructor() {
    std::string firstNameGiven{"Vladislav"};
    std::string middleNameGiven{"Viktorovich"};
    std::string lastNameGiven{"Kovyazin"};
    std::string courseGiven{"MATH1"};
    std::string date{"28.12.2019"};

    WateringRecord origin(date, firstNameGiven, middleNameGiven,
                          lastNameGiven, courseGiven, 10);
    WateringRecord copy(origin);
    assert(compareWateringRecord(origin, copy));
    copy.setStudent(Student{"test",
                            "test",
                            "test",
                            "test"});
    copy.setDate("28.11.2020");
    copy.setRecordValue(15);
    assert(!compareStudents(copy.getStudent(), origin.getStudent()));
    assert(!compareDates(copy.getDate(), origin.getDate()));
    assert(!compareWateringVolume(copy.getRecordValue(),
                                  origin.getRecordValue()));
}


// test get methods

void testGetStudent(const WateringRecord &record,
                    const Student &originStudent) {
    const Student &fetchedStudent = record.getStudent();
    assert(compareStudents(originStudent, fetchedStudent));
}

void testGetDate(const WateringRecord &record, const std::string &originDate) {
    const std::string &fetchedDate = record.getDate();
    assert(compareDates(originDate, fetchedDate));
}

void testGetWateringVolume(const WateringRecord &record,
                           const float &originWateringVolume) {
    const float &fetchedWateringVolume = record.getRecordValue();
    assert(compareWateringVolume(originWateringVolume, fetchedWateringVolume));
}

void testSetStudent(WateringRecord &record) {
    std::string firstName{"test"};
    std::string middleName{"test"};
    std::string lastName{"test"};
    std::string course{"test"};
    Student testStudent{firstName, middleName, lastName, course};
    record.setStudent(testStudent);
    assert(compareStudents(record.getStudent(), testStudent));
}

void testSetDate(WateringRecord &record) {
    std::stringstream streamDate;
    streamDate << 28 << "." << 2 << "." << 2020;
    std::string testDate = streamDate.str();
    record.setDate(testDate);
    assert(compareDates(record.getDate(), testDate));
}

void testSetWateringVolume(WateringRecord &record) {
    const float testWateringVolume = 2;
    record.setRecordValue(testWateringVolume);
    assert(compareWateringVolume(record.getRecordValue(),
                                 testWateringVolume));

}

WateringRecord sampleRecord() {
    std::string firstNameGiven{"Vladislav"};
    std::string middleNameGiven{"Viktorovich"};
    std::string lastNameGiven{"Kovyazin"};
    std::string courseGiven{"MATH1"};
    std::stringstream streamDate;
    streamDate << 28 << "." << 3 << "." << 2020;
    std::string date = streamDate.str();
    float pouredWater = 2;
    WateringRecord record = testWateringRecordConstruction(
            date,
            firstNameGiven, middleNameGiven, lastNameGiven, courseGiven,
            pouredWater
    );
    return record;
}


void startTesting() {
    std::string firstNameGiven{"Vladislav"};
    std::string middleNameGiven{"Viktorovich"};
    std::string lastNameGiven{"Kovyazin"};
    std::string courseGiven{"MATH1"};
    std::stringstream streamDate;
    streamDate << 28 << "." << 2 << "." << 2020;
    std::string date = streamDate.str();
    float pouredWater = 10;
    WateringRecord record = testWateringRecordConstruction(
            date,
            firstNameGiven, middleNameGiven, lastNameGiven, courseGiven,
            pouredWater
    );
    testCopyConstructor();
    testGetStudent(record, Student{firstNameGiven,
                                   middleNameGiven,
                                   lastNameGiven,
                                   courseGiven});
    testGetDate(record, date);
    testGetWateringVolume(record, pouredWater);
    testSetStudent(record);
    testSetDate(record);
    testSetWateringVolume(record);
}


void printCollection(RecordsCollection &collection) {
    for (int i = 0; i < collection.getLength(); i++) {
        std::cout << i + 1 << " ";
        std::cout << collection.at(i).getDate() << " ";
        std::cout << collection.at(i).getStudent().lastName << " ";
        std::cout << collection.at(i).getStudent().firstName << " ";
        std::cout << collection.at(i).getStudent().middleName << " ";
        std::cout << collection.at(i).getStudent().course << " ";
        std::cout << "Water: " << collection.at(i).getRecordValue() << "\n";
    }

}

void testCompareCollection() {
    WateringRecord sample = sampleRecord();
    RecordsCollection first{};
    RecordsCollection second{};
    first.addRecord(sample);
    first.addRecord(sample);
    second.addRecord(sample);
    assert(!first.compare(second));
    second.addRecord(sample);
    assert(first.compare(second));
    first.addRecord(sample);
    sample.setRecordValue(sample.getRecordValue() + 1);
    assert(!first.compare(second));
}

void testCollectionCopyConstructor(const RecordsCollection &origin) {
    RecordsCollection copy = RecordsCollection(origin);
    assert(copy.compare(origin));
    WateringRecord sample = sampleRecord();
    copy.addRecord(sample);
    assert(!copy.compare(origin));
}

void testCollectionConstructor() {
    RecordsCollection newCollection{};
    assert(newCollection.getLength() == 0);
}

void testAddElements(RecordsCollection &origin) {
    WateringRecord sample = sampleRecord();
    origin.addRecord(sample);
    assert(origin.at(origin.getLength() - 1).compare(sample));
    origin.setAt(sample, 0);
    assert(origin.at(0).compare(sample));
    sample.setDate("29.3.2021");
    origin.insertAt(sample, 0);
    assert(origin.at(0).compare(sample));
}

void testDeleteElements(RecordsCollection &origin) {
    assert(origin.getLength() >= 2);
    RecordsCollection copy{origin};
    origin.deleteRecord(0);
    assert(origin.at(0).compare(copy.at(1)));
    origin.erase();
    RecordsCollection empty{};
    assert(origin.compare(empty));
}

void testWriteToFile() {
    RecordsCollection collection{};
    RecordsCollection loadCollection{};
    WateringRecord sample = sampleRecord();
    std::string path{"C:\\dev\\OOP\\First lab\\tests.txt"};
    collection.writeToFile(path);
    std::fstream file;
    file.open(path);
    std::string line;
    while (std::getline(file, line)) {
        auto offset = 0;
        int index = stoi(line.substr(offset, line.find(' ')));
        offset += line.find(' ') + 1;
        std::string date = line.substr(offset,
                                       line.find(' ', offset) - offset);
        offset += date.length() + 1;
        std::string lastName = line.substr(offset,
                                           line.find(' ', offset) - offset);
        offset += lastName.length() + 1;
        std::string firstName = line.substr(offset,
                                            line.find(' ', offset) - offset);
        offset += firstName.length() + 1;
        std::string middleName = line.substr(offset,
                                             line.find(' ', offset) - offset);
        offset += middleName.length() + 1;
        std::string course = line.substr(offset,
                                         line.find(' ', offset) - offset);
        float wateringVolume = stof(line.substr(line.rfind(' ') + 1,
                                                line.length()));
        WateringRecord record{date,
                              firstName, middleName, lastName, course,
                              wateringVolume};
        loadCollection.addRecord(record);
    }
    file.close();
    assert(collection.compare(loadCollection));
}

void testLoadFromFile() {
    RecordsCollection collection{};
    RecordsCollection loadCollection{};
    WateringRecord sample = sampleRecord();
    std::string path{"C:\\dev\\OOP\\First lab\\tests.txt"};
    collection.writeToFile(path);
    loadCollection.loadFromFile(path);
    assert(collection.compare(loadCollection));
}

void testCollection() {
    testCollectionConstructor();
    testCompareCollection();
    RecordsCollection collection{};
    collection.loadFromFile("C:\\dev\\OOP\\First lab\\test.txt");
    collection.checkChronologicalOrder();
    collection.checkGrooming();
    testCollectionCopyConstructor(collection);
    testAddElements(collection);
    testDeleteElements(collection);
    testWriteToFile();
    testLoadFromFile();
}

int main() {
    // start tests
    startTesting();
    testCollection();
    std::cout << "Tests passed!" << "\n";


    return 0;
}
