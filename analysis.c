#include <stdio.h>
#include <stdint.h>

int main() {
    FILE *inputFile;
    int count;

    uint64_t number1, number2;

    // open the file for reading
    inputFile = fopen("output.txt", "r");
    if (inputFile == NULL) {
        perror("Error opening numbers.txt for reading");
        return 1;
    }

    // read the additional value (count) from the file
    if (fscanf(inputFile, "%d", &count) != 1) {
        fprintf(stderr, "Error reading count from output.txt\n");
        fclose(inputFile);
        return 1;
    }

    // read the two numbers from the file
    if (fscanf(inputFile, "%llu %llu", &number2, &number1) != 2) {
        fprintf(stderr, "Error reading two numbers from numbers.txt\n");
        fclose(inputFile);
        return 1;
    }

    // close the file
    fclose(inputFile);

    // print the results
    printf("OVERALL:\n");
    printf("Time taken while using sha256: %llu nanoseconds\n", (unsigned long long)number1);
    printf("Time taken without using sha256: %llu nanoseconds\n", (unsigned long long)number2);

    double percentage_difference = ((number1 - number2) / ((double)(number1 + number2) / 2.0)) * 10000.0;
    double absolute_difference = (double)(number1 - number2);
    double factor = percentage_difference / 100.0;
    printf("Percentage Difference: %.2f%%\n", percentage_difference);
    printf("Difference Factor: %.2fx\n", factor);
    printf("Absolute Difference: %.0f nanoseconds\n", absolute_difference);
    printf("\n");

    printf("AVERAGES BASED ON %d PACKETS:\n", count);
    double average_time_with_sha256 = (double)number1 / count;
    double average_time_without_sha256 = (double)number2 / count;
    printf("Average Time per Packet with sha256: %.2f nanoseconds\n", average_time_with_sha256);
    printf("Average Time per Packet without sha256: %.2f nanoseconds\n", average_time_without_sha256);
    printf("Average Difference Factor: %.2fx\n", factor);
    double avg_percentage_difference = ((average_time_with_sha256 - average_time_without_sha256) / ((double)(average_time_with_sha256 + average_time_without_sha256) / 2.0)) * 10000.0;
    double avg_absolute_difference = (double)(average_time_with_sha256 - average_time_without_sha256);
    double avg_factor = avg_percentage_difference / 100.0;
    printf("Average Percentage Difference: %.2f%%\n", avg_percentage_difference);
    printf("Average Difference Factor: %.2fx\n", factor);
    printf("Average Absolute Difference: %.0f nanoseconds\n", avg_absolute_difference);


    return 0;

    // seems to be very close to around 195x for everything
}



// gcc analysis.c -o analysis
// sudo ./analysis