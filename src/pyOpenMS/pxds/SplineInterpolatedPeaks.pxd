from Types cimport *
from MSSpectrum cimport *
from MSChromatogram cimport *
from SplinePackage cimport *
from Peak1D cimport *

cdef extern from "<OpenMS/FILTERING/DATAREDUCTION/SplineInterpolatedPeaks.h>" namespace "OpenMS":
    
    cdef cppclass SplineInterpolatedPeaks "OpenMS::SplineInterpolatedPeaks":

        SplineInterpolatedPeaks(libcpp_vector[double] mz, libcpp_vector[double] intensity) nogil except +

        SplineInterpolatedPeaks(MSSpectrum raw_spectrum) nogil except +

        SplineInterpolatedPeaks(MSChromatogram raw_chromatogram) nogil except +

        double getPosMin() nogil except +

        double getPosMax() nogil except +

        int size() nogil except +
        
        Navigator getNavigator(double scaling) nogil except +


cdef extern from "<OpenMS/FILTERING/DATAREDUCTION/SplineInterpolatedPeaks.h>" namespace "OpenMS::SplineInterpolatedPeaks":
    
    cdef cppclass Navigator:
        
            Navigator() nogil except + #wrap-ignore
            Navigator(Navigator) nogil except + #wrap-ignore
            
            Navigator(libcpp_vector[SplinePackage]* packages, double posMin, double posMax, double scaling)  nogil except +

            double eval(double pos) nogil except +

            double getNextPos(double pos) nogil except +
