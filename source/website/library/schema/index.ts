/// Vendor Modules
import { z } from 'zod';
import { metaSchema, pageSchema } from 'fumadocs-core/source/schema';

/** Collection Schema Properties. */
export namespace Schema {
    //  PROPERTIES  //

    /** Prepare a baseline draft schema property. */
    export const draft = z.boolean().optional();

    /** Prepare a baseline date schema property. */
    export const date = z.iso.date().or(z.date());

    /** Prepare a baseline author schema property. */
    export const author = z.string();

    /** Prepare a baseline revision schema property. */
    export const revision = z.int().min(0);

    /** Extend the baseline page-schema to be used. */
    export const page = pageSchema.extend({ draft });

    /** Extend the baseline meta-schema to be used. */
    export const meta = metaSchema;
}
