while (<>) {
    s/\(([^)]+)\)/\(\)/g;
    print;
}