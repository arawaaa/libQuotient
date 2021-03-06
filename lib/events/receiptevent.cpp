// SPDX-FileCopyrightText: 2018 Kitsune Ral <Kitsune-Ral@users.sf.net>
// SPDX-License-Identifier: LGPL-2.1-or-later

/*
Example of a Receipt Event:
{
    "content": {
        "$1435641916114394fHBLK:matrix.org": {
            "m.read": {
                "@rikj:jki.re": {
                    "ts": 1436451550453
                }
            }
        }
    },
    "room_id": "!KpjVgQyZpzBwvMBsnT:matrix.org",
    "type": "m.receipt"
}
*/

#include "receiptevent.h"

#include "converters.h"
#include "logging.h"

using namespace Quotient;

EventsWithReceipts ReceiptEvent::eventsWithReceipts() const
{
    EventsWithReceipts result;
    const auto& contents = contentJson();
    result.reserve(contents.size());
    for (auto eventIt = contents.begin(); eventIt != contents.end(); ++eventIt) {
        if (eventIt.key().isEmpty()) {
            qCWarning(EPHEMERAL)
                << "ReceiptEvent has an empty event id, skipping";
            qCDebug(EPHEMERAL) << "ReceiptEvent content follows:\n" << contents;
            continue;
        }
        const auto reads =
            eventIt.value().toObject().value("m.read"_ls).toObject();
        QVector<Receipt> receipts;
        receipts.reserve(reads.size());
        for (auto userIt = reads.begin(); userIt != reads.end(); ++userIt) {
            const auto user = userIt.value().toObject();
            receipts.push_back(
                { userIt.key(), fromJson<QDateTime>(user["ts"_ls]) });
        }
        result.push_back({ eventIt.key(), std::move(receipts) });
    }
    return result;
}
