// ----------------------------------------------------------------------------
// BLANK.h  --  BASIS FOR ALL MODEMS
//
// Copyright (C) 2024
//		Benjamin Cance, KC8BWS
//
// This file is part of fldigi.
//
// Fldigi-Improved is free software: you can redistribute it and/or modify
// it under the terms of the MIT License.
// ----------------------------------------------------------------------------

#ifndef BLANK_H
#define BLANK_H

#include <memory>
#include <array>
#include "trx.h"
#include "modem.h"
#include "fft.h"
#include "filters.h"
#include "complex.h"

constexpr int BLANK_SAMPLE_RATE = 8000;
constexpr int SYM_LEN = 512;
constexpr int BLANK_BW = 100;

constexpr int BUFF_LEN = 4096;
constexpr int SCOPE_DATA_LEN = 1024;

class BLANK : public modem {
protected:
    double phaseacc;
    double phaseincr;

    std::unique_ptr<C_FIR_filter> bandpass;
    std::unique_ptr<C_FIR_filter> lowpass;
    std::unique_ptr<C_FIR_filter> hilbert;
    std::unique_ptr<Cmovavg> moving_avg;
    std::unique_ptr<sfft> slidingfft;

    int symlen;
    // receive
    std::array<double, SCOPE_DATA_LEN> scope_data;
    std::array<double, BUFF_LEN> inbuf;
    // transmit
    int txstate;

    std::array<double, SYM_LEN> outbuf;
    unsigned int buffptr;

public:
    BLANK();
    ~BLANK() override;
    void init() override;
    void rx_init() override;
    void tx_init(SoundBase *sc) override;
    void restart() override;
    int rx_process(const double *buf, int len) override;
    int tx_process() override;
    void update_syncscope();
};

#endif
