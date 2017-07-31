#ifndef CPD_DSP_H
#define CPD_DSP_H

#include "cpd_def.h"
#include "cpd_types.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Switches DSP processing
 * @param state - 1 to enable, 0 - to disable 
 * @return 1 on success, 0 on error
 */
CPD_EXTERN int cpd_dsp_switch(int state);

struct _cpd_audio_devlist;
typedef struct _cpd_audio_devlist t_cpd_audio_devlist;

CPD_EXTERN t_cpd_audio_devlist* cpd_audio_devlist_new();
CPD_EXTERN void cpd_audio_devlist_free(t_cpd_audio_devlist* l);

CPD_EXTERN size_t cpd_audio_input_devices_num(t_cpd_audio_devlist* devl);
CPD_EXTERN size_t cpd_audio_output_devices_num(t_cpd_audio_devlist* devl);
CPD_EXTERN const char* cpd_audio_input_device_name(t_cpd_audio_devlist* devl, size_t n);
CPD_EXTERN const char* cpd_audio_output_device_name(t_cpd_audio_devlist* devl, size_t n);

/**
 * Starts DSP mainloop in separate thread. Only single thread is allowed
 * @return 1 on success, or 0 if thread creation failed.
 */
CPD_EXTERN int cpd_dsp_thread_start();

/**
 * Stops DSP mainloop thread and waits it for finished.
 * @return 1 on success or 0 on error
 */
CPD_EXTERN int cpd_dsp_thread_stop();

#ifdef __cplusplus
}
#endif

#endif // CPD_DSP_H
