#pragma once
#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <cstdio>
#include <cstdlib>
#include <cstring>

#define MAX_SECTION 64
#define MAX_KEY 64
#define MAX_VALUE 256
#define MAX_LINE 512

typedef struct {
    char key[MAX_KEY];
    char value[MAX_VALUE];
} IniPair;

typedef struct {
    char section[MAX_SECTION];
    IniPair* pairs;
    int pair_count;
} IniSection;

typedef struct {
    IniSection* sections;
    int section_count;
} IniFile;

class FileManager {
public:
    static IniFile* load_ini(const char* filename);
    static const char* get_value(IniFile* ini, const char* section, const char* key);
    static void set_value(IniFile* ini, const char* section, const char* key, const char* value);
    static void save_ini(const IniFile* ini, const char* filename);
    static void free_ini(IniFile* ini);
    static void initialize_default_values(IniFile* ini);
};

#endif
