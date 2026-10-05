#include <stdio.h>
#include <math.h>

/*
 * STRUCT CHUA TOI UU
 * Thu tu thanh phan duoc sap xep xen ke
 * giua cac kieu du lieu co alignment khac nhau.
 */
struct DeviceUnoptimized {
    char status;
    double voltage;
    char warning;
    int deviceID;
    double current;
    float measuredPower;
    int operatingMinutes;
};

/*
 * STRUCT DA TOI UU
 * Sap xep cac thanh phan theo nhom kich thuoc/alignment.
 */
struct DeviceOptimized {
    double voltage;
    double current;
    float measuredPower;
    int deviceID;
    int operatingMinutes;
    char status;
    char warning;
};

int main() {
    struct DeviceOptimized device;

    float calculatedPower;
    float difference;
    float differencePercent;
    float energyKWh;

    printf("========================================\n");
    printf(" SMART HOME - ENERGY SAFETY MONITOR\n");
    printf("========================================\n");

    /*
     * SO SANH KICH THUOC STRUCT
     */
    printf("\n--- PHAN TICH BO NHO ---\n");
    printf("sizeof(DeviceUnoptimized): %zu bytes\n",
           sizeof(struct DeviceUnoptimized));

    printf("sizeof(DeviceOptimized)  : %zu bytes\n",
           sizeof(struct DeviceOptimized));

    printf("\n--- NHAP THONG TIN THIET BI ---\n");

    printf("Nhap ma thiet bi: ");
    scanf("%d", &device.deviceID);

    printf("Nhap trang thai (0-Tat, 1-Bat): ");
    scanf("%hhd", &device.status);

    printf("Nhap dien ap U (V): ");
    scanf("%lf", &device.voltage);

    printf("Nhap dong dien I (A): ");
    scanf("%lf", &device.current);

    printf("Nhap cong suat do duoc (W): ");
    scanf("%f", &device.measuredPower);

    printf("Nhap thoi gian hoat dong (phut): ");
    scanf("%d", &device.operatingMinutes);

    if (device.voltage <= 0) {
        printf("\n[LOI] Dien ap U phai lon hon 0.\n");
        return 0;
    }

    if (device.current < 0) {
        printf("\n[LOI] Dong dien I khong duoc am.\n");
        return 0;
    }

    if (device.operatingMinutes < 0) {
        printf("\n[LOI] Thoi gian hoat dong khong duoc am.\n");
        return 0;
    }

    if (device.status != 0 && device.status != 1) {
        printf("\n[LOI] Trang thai chi duoc la 0 hoac 1.\n");
        return 0;
    }

    calculatedPower =
        (float)(device.voltage * device.current);

    printf("\n--- KET QUA PHAN TICH ---\n");

    printf("Cong suat tinh toan: %.2f W\n",
           calculatedPower);

    printf("Cong suat cam bien : %.2f W\n",
           device.measuredPower);

    difference =
        fabsf(device.measuredPower - calculatedPower);

    if (calculatedPower > 0) {

        differencePercent =
            (difference / calculatedPower) * 100.0f;

        printf("Do sai lech: %.2f%%\n",
               differencePercent);

        if (differencePercent > 5.0f) {
            printf("[CANH BAO] Cam bien cong suat bao sai lech.\n");
        } else {
            printf("[OK] Cam bien cong suat trong gioi han 5%%.\n");
        }

    } else {

        if (device.measuredPower != 0) {
            printf("[CANH BAO] Cam bien cong suat bao sai lech.\n");
        } else {
            printf("[OK] Cong suat cam bien hop le.\n");
        }
    }

    if (device.current > 30.0 ||
        calculatedPower > 6600.0f) {

        printf("[CANH BAO] QUA TAI NGUY HIEM.\n");

    } else {

        printf("[OK] Khong phat hien qua tai.\n");
    }

    if (device.status == 0 &&
        device.current > 0.05) {

        printf("[CANH BAO] RO RI DIEN HOAC TAI AN.\n");

    } else {

        printf("[OK] Khong phat hien ro ri dien.\n");
    }
    energyKWh =
        calculatedPower *
        ((float)device.operatingMinutes / 60.0f)
        / 1000.0f;

    printf("\n========================================\n");
    printf("           BAO CAO CUOI\n");
    printf("========================================\n");

    printf("Ma thiet bi       : %d\n",
           device.deviceID);

    printf("Trang thai        : %s\n",
           device.status == 1 ? "BAT" : "TAT");

    printf("Dien ap           : %.2f V\n",
           device.voltage);

    printf("Dong dien         : %.2f A\n",
           device.current);

    printf("Cong suat tinh    : %.2f W\n",
           calculatedPower);

    printf("Cong suat do      : %.2f W\n",
           device.measuredPower);

    printf("Thoi gian         : %d phut\n",
           device.operatingMinutes);

    printf("Dien nang         : %.4f kWh\n",
           energyKWh);

    printf("========================================\n");

    return 0;
}
