#ifndef _KalmanFilter_h
#define _KalmanFilter_h

class KalmanFilter {
   public:
    KalmanFilter(double mea_e, double est_e, double q);
    double updateEstimate(double mea);
    void setMeasurementError(double mea_e);
    void setEstimateError(double est_e);
    void setProcessNoise(double q);
    double getKalmanGain();
    double getEstimateError();

   private:
    double _err_measure;
    double _err_estimate;
    double _q;
    double _current_estimate = 0;
    double _last_estimate = 0;
    double _kalman_gain = 0;
};

#endif
