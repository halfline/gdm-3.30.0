/* -*- Mode: C; tab-width: 8; indent-tabs-mode: nil; c-basic-offset: 8 -*-
 *
 * Copyright (C) 2012 Red Hat, Inc.
 * Copyright (C) 2012 Giovanni Campagna <scampa.giovanni@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 */

#ifndef __GDM_CLIENT_H
#define __GDM_CLIENT_H

#include <glib-object.h>
#include "gdm-client-glue.h"

G_BEGIN_DECLS

#define GDM_TYPE_CLIENT         (gdm_client_get_type ())
#define GDM_CLIENT(o)           (G_TYPE_CHECK_INSTANCE_CAST ((o), GDM_TYPE_CLIENT, GdmClient))
#define GDM_CLIENT_CLASS(k)     (G_TYPE_CHECK_CLASS_CAST((k), GDM_TYPE_CLIENT, GdmClientClass))
#define GDM_IS_CLIENT(o)        (G_TYPE_CHECK_INSTANCE_TYPE ((o), GDM_TYPE_CLIENT))
#define GDM_IS_CLIENT_CLASS(k)  (G_TYPE_CHECK_CLASS_TYPE ((k), GDM_TYPE_CLIENT))
#define GDM_CLIENT_GET_CLASS(o) (G_TYPE_INSTANCE_GET_CLASS ((o), GDM_TYPE_CLIENT, GdmClientClass))

typedef struct GdmClientPrivate GdmClientPrivate;

typedef struct
{
        GObject                  parent;
        GdmClientPrivate *priv;
} GdmClient;

typedef struct
{
        GObjectClass   parent_class;

} GdmClientClass;

#define GDM_CLIENT_ERROR (gdm_client_error_quark ())

typedef enum _GdmClientError {
        GDM_CLIENT_ERROR_GENERIC = 0,
} GdmClientError;

GType              gdm_client_get_type                 (void);
GQuark             gdm_client_error_quark              (void);

GdmClient         *gdm_client_new                      (void);
void               gdm_client_set_enabled_extensions   (GdmClient *client,
                                                        const char * const * extensions);

void               gdm_client_open_reauthentication_channel (GdmClient     *client,
                                                             const char           *username,
                                                             GCancellable         *cancellable,
                                                             GAsyncReadyCallback   callback,
                                                             gpointer              user_data);

GdmUserVerifier   *gdm_client_open_reauthentication_channel_finish (GdmClient  *client,
                                                                    GAsyncResult      *result,
                                                                    GError           **error);

GdmUserVerifier   *gdm_client_open_reauthentication_channel_sync (GdmClient *client,
                                                                  const char       *username,
                                                                  GCancellable     *cancellable,
                                                                  GError          **error);

void               gdm_client_get_user_verifier         (GdmClient     *client,
                                                         GCancellable         *cancellable,
                                                         GAsyncReadyCallback   callback,
                                                         gpointer              user_data);
GdmUserVerifier   *gdm_client_get_user_verifier_finish  (GdmClient     *client,
                                                         GAsyncResult         *result,
                                                         GError              **error);
GdmUserVerifier   *gdm_client_get_user_verifier_sync    (GdmClient *client,
                                                         GCancellable     *cancellable,
                                                         GError          **error);

GdmUserVerifierChoiceList *gdm_client_get_user_verifier_choice_list  (GdmClient *client);

void               gdm_client_get_greeter               (GdmClient     *client,
                                                         GCancellable         *cancellable,
                                                         GAsyncReadyCallback   callback,
                                                         gpointer              user_data);
GdmGreeter        *gdm_client_get_greeter_finish        (GdmClient *client,
                                                         GAsyncResult     *result,
                                                         GError          **error);
GdmGreeter        *gdm_client_get_greeter_sync          (GdmClient *client,
                                                         GCancellable     *cancellable,
                                                         GError          **error);

void               gdm_client_get_remote_greeter        (GdmClient     *client,
                                                         GCancellable         *cancellable,
                                                         GAsyncReadyCallback   callback,
                                                         gpointer              user_data);
GdmRemoteGreeter  *gdm_client_get_remote_greeter_finish (GdmClient *client,
                                                         GAsyncResult     *result,
                                                         GError          **error);
GdmRemoteGreeter  *gdm_client_get_remote_greeter_sync   (GdmClient *client,
                                                         GCancellable     *cancellable,
                                                         GError          **error);

void               gdm_client_get_chooser               (GdmClient     *client,
                                                         GCancellable         *cancellable,
                                                         GAsyncReadyCallback   callback,
                                                         gpointer              user_data);
GdmChooser        *gdm_client_get_chooser_finish        (GdmClient *client,
                                                         GAsyncResult     *result,
                                                         GError          **error);
GdmChooser        *gdm_client_get_chooser_sync          (GdmClient *client,
                                                         GCancellable     *cancellable,
                                                         GError          **error);

#if GLIB_CHECK_VERSION(2, 44, 0)
G_DEFINE_AUTOPTR_CLEANUP_FUNC (GdmClient, g_object_unref)
#endif

G_END_DECLS

#endif /* __GDM_CLIENT_H */
