#pragma once

class Geopoint {
public:
    Geopoint(double _lat, double _lng, double _elev = 0)
        : lat(_lat), lng(_lng), elev(_elev) {}

    // ������
    double latitude() const { return lat; }

    // �������
    double longitude() const { return lng; }

    // ������ ��� ������� ����
    double elevation() const { return elev; }

    // ���������� �� ������ �����
    double distanceTo(const Geopoint &other);

private:
    double lat, lng, elev;
};
