/**************************************************************************/
/*                                                                        */
/*       Copyright (c) Microsoft Corporation. All rights reserved.        */
/*                                                                        */
/*       This software is licensed under the Microsoft Software License   */
/*       Terms for Microsoft Azure RTOS. Full text of the license can be  */
/*       found in the LICENSE file at https://aka.ms/AzureRTOS_EULA       */
/*       and in the root directory of this software.                      */
/*                                                                        */
/**************************************************************************/


/**************************************************************************/
/**************************************************************************/
/**                                                                       */
/** NetX Secure Component                                                 */
/**                                                                       */
/**    Transport Layer Security (TLS)                                     */
/**                                                                       */
/**************************************************************************/
/**************************************************************************/

#define NX_SECURE_SOURCE_CODE


#include "nx_secure_tls.h"

/* Bring in externs for caller checking code.  */

NX_SECURE_CALLER_CHECKING_EXTERNS

/**************************************************************************/
/*                                                                        */
/*  FUNCTION                                               RELEASE        */
/*                                                                        */
/*    _nxe_secure_tls_session_renegotiate_callback_set    PORTABLE C      */
/*                                                           6.0.2        */
/*  AUTHOR                                                                */
/*                                                                        */
/*    Timothy Stapko, Microsoft Corporation                               */
/*                                                                        */
/*  DESCRIPTION                                                           */
/*                                                                        */
/*    This function checks for errors when setting the TLS session        */
/*    re-negotiation callback function pointer.                           */
/*                                                                        */
/*  INPUT                                                                 */
/*                                                                        */
/*    tls_session                           TLS control block             */
/*    func_ptr                              Pointer to callback function  */
/*                                                                        */
/*  OUTPUT                                                                */
/*                                                                        */
/*    status                                Completion status             */
/*                                                                        */
/*  CALLS                                                                 */
/*                                                                        */
/*    _nx_secure_tls_session_renegotiate_callback_set                     */
/*                                          Actual function pointer set   */
/*                                                                        */
/*  CALLED BY                                                             */
/*                                                                        */
/*    Application Code                                                    */
/*                                                                        */
/*  RELEASE HISTORY                                                       */
/*                                                                        */
/*    DATE              NAME                      DESCRIPTION             */
/*                                                                        */
/*  05-19-2020     Timothy Stapko           Initial Version 6.0           */
/*  08-14-2020     Timothy Stapko           Modified comment(s),          */
/*                                            fixed renegotiation bug,    */
/*                                            resulting in version 6.0.2  */
/*                                                                        */
/**************************************************************************/
#ifndef NX_SECURE_TLS_DISABLE_SECURE_RENEGOTIATION
UINT _nxe_secure_tls_session_renegotiate_callback_set(NX_SECURE_TLS_SESSION *tls_session,
                                                      ULONG (*func_ptr)(NX_SECURE_TLS_SESSION *session))
{
UINT status;


    if (tls_session == NX_NULL || func_ptr == NX_NULL)
    {
        return(NX_PTR_ERROR);
    }

    /* Make sure the session is initialized. */
    if(tls_session -> nx_secure_tls_id != NX_SECURE_TLS_ID)
    {
        return(NX_SECURE_TLS_SESSION_UNINITIALIZED);
    }

    /* Check for appropriate caller.  */
    NX_THREADS_ONLY_CALLER_CHECKING

    /* We want to be able to set the function to NX_NULL to disable it, so don't check for it. */
    status = _nx_secure_tls_session_renegotiate_callback_set(tls_session, func_ptr);

    return(status);
}
#endif /* NX_SECURE_TLS_DISABLE_SECURE_RENEGOTIATION */

