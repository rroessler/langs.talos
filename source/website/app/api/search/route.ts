/// Vendor Modules
import { createFromSource } from 'fumadocs-core/search/server';

/// Library Modules
import { Source } from '@/website/source';

/** Ensures statically cached. */
export const revalidate = false;

/** The exposed "GET" method. */
export const { staticGET: GET } = createFromSource(Source.docs);
